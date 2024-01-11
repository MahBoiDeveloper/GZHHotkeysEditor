#include <QApplication>
#include <QFile>
#include <QDebug>

#include "../../Logger.hpp"
#include "../gui_config.hpp"
#include "configurationDialogs/creation_dialog.hpp"
#include "configurationDialogs/load_dialog.hpp"
#include "stacked_launch_widget.hpp"

StackedLaunchWidget::StackedLaunchWidget(Config::Languages lngType, QWidget *parent) : QStackedWidget(parent)
{
    // Application style settings
    QFile styleSheetsFile{":/my/css/mainStyleSheet.css"};

    if (styleSheetsFile.open(QIODevice::ReadOnly))
    {
        qApp->setStyleSheet(styleSheetsFile.readAll());
        styleSheetsFile.close();
    }
    else
        LOGMSG("Unable to read the style file mainStyleSheet.css.");

    qApp->setWindowIcon(QIcon(QPixmap::fromImage(GuiConfig::decodeDefaultWebpIcon())));

    // MainLaunchWidget settings
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);
    
    SetTranslator(lngType);
    pStartWidget = new GreetingWidget(lngType, this);
    addWidget(pStartWidget);
    UpdateConnectionsToSignals();
}

/// @brief Set or reset translator for start window.
void StackedLaunchWidget::SetTranslator(Config::Languages lngType)
{
    // Delete old translator
    if (pTranslator != nullptr) QCoreApplication::removeTranslator(pTranslator);

    // Create new translator
    if (lngType != Config::Languages::English)
    {
        pTranslator = new QTranslator;
        pTranslator->load(Config::GetLocaleFromLangEnum(lngType),
                         Config::translationsPath);
        QCoreApplication::installTranslator(pTranslator);
    }
}

/// @brief Call this fucntion on every new pointer of pStartWidget.
void StackedLaunchWidget::UpdateConnectionsToSignals()
{
    connect(pStartWidget, &GreetingWidget::languageChanged,
            this,         &StackedLaunchWidget::OnChangeLanguage);
    connect(pStartWidget, &GreetingWidget::pressed,
            this,         &StackedLaunchWidget::OnStartButtonClicked);
}

void StackedLaunchWidget::OnChangeLanguage(int intLngIndex)
{
    // Find language type by its code.
    Config::Languages lngType = static_cast<Config::Languages>(intLngIndex);

    // Change class' translator.
    SetTranslator(lngType);

    // Recreate StartWidget and update connections.
    pStartWidget->deleteLater();
    pStartWidget = new GreetingWidget(lngType);
    addWidget(pStartWidget);
    UpdateConnectionsToSignals();
}

/// @brief Open create/loader widget.
void StackedLaunchWidget::OnStartButtonClicked(GreetingWidget::StandartButtons standartButton)
{
    BaseConfigurationDialog* configurationWidget = nullptr;

    switch (standartButton)
    {
    case GreetingWidget::StandartButtons::NewProject:
        configurationWidget = new CreationDialog;
        break;
    case GreetingWidget::StandartButtons::LoadProject:
        configurationWidget = new LoadDialog;
        break;
    default:
        configurationWidget = new CreationDialog;
        break;
    }
    addWidget(configurationWidget);
    setCurrentWidget(configurationWidget); // next window (creator)

    // if accepted -> create redactor with configs and delete other widgets
    connect(configurationWidget, &CreationDialog::acceptedConfiguration, 
            this,                &StackedLaunchWidget::OnConfigurationAccepted);
}

// close and create new editor
void StackedLaunchWidget::OnConfigurationAccepted(const QVariant& configuration)
{
    LOGMSG("Loading hotkey editor window...");
    pHotkeysEditor = new HotkeysMainWindow(configuration);
    pHotkeysEditor->setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");
    pHotkeysEditor->show();
    LOGMSG("Hotkey editor window has been loaded");
    LOGMSG("Closing and deleting the StartWidget");
    close();
    pStartWidget->deleteLater();
}
