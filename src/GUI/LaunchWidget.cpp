#include <QApplication>
#include <QFile>
#include <QDebug>

#include "../Logger.hpp"
#include "GUIConfig.hpp"
#include "CreationDialog.hpp"
#include "LoadDialog.hpp"
#include "LaunchWidget.hpp"

LaunchWidget::LaunchWidget(Config::Languages lngType, QWidget* parent) : QStackedWidget(parent)
{
    // Application style settings
    QFile styleSheetsFile{":/my/css/mainStyleSheet.css"};

    if (styleSheetsFile.open(QIODevice::ReadOnly))
    {
        qApp->setStyleSheet(styleSheetsFile.readAll());
        styleSheetsFile.close();
    }
    else
    {
        LOGMSG("Unable to read the style file mainStyleSheet.css.");
    }

    qApp->setWindowIcon(QIcon(QPixmap::fromImage(GUIConfig::DecodeDefaultWebpIcon())));

    // MainLaunchWidget settings
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);
    
    SetTranslator(lngType);
    pStartWidget = new GreetingWidget{lngType};
    addWidget(pStartWidget);
    UpdateConnectionsToSignals();
}

void LaunchWidget::SetTranslator(Config::Languages lngType)
{
    // Delete old translator
    if (pTranslator != nullptr) QCoreApplication::removeTranslator(pTranslator);

    // Create new translator
    if (lngType != Config::Languages::English)
    {
        pTranslator = new QTranslator;
        pTranslator->load(Config::GetLanguageShortName(lngType),
                          Config::TRANSLATIONS_FOLDER);
        QCoreApplication::installTranslator(pTranslator);
    }
}

void LaunchWidget::UpdateConnectionsToSignals()
{
    connect(pStartWidget, &GreetingWidget::languageChanged,
            this,         &LaunchWidget::OnChangeLanguage);
    connect(pStartWidget, &GreetingWidget::pressed,
            this,         &LaunchWidget::OnStartButtonClicked);
}

void LaunchWidget::OnChangeLanguage(int intLngIndex)
{
    // Find language type by its code.
    Config::Languages lngType = static_cast<Config::Languages>(intLngIndex);

    // Change class' translator.
    SetTranslator(lngType);

    // Recreate StartWidget and update connections.
    pStartWidget->deleteLater();
    pStartWidget = new GreetingWidget{lngType};
    addWidget(pStartWidget);
    UpdateConnectionsToSignals();
}

void LaunchWidget::OnStartButtonClicked(GreetingWidget::StandartButtons standartButton)
{
    BaseConfigurationDialog* pConfigurationWidget = nullptr;

    switch (standartButton)
    {
        case GreetingWidget::StandartButtons::NewProject:
            pConfigurationWidget = new CreationDialog();
            break;
        case GreetingWidget::StandartButtons::LoadProject:
            pConfigurationWidget = new LoadDialog();
            break;
        default:
            pConfigurationWidget = new CreationDialog();
            break;
    }
    addWidget(pConfigurationWidget);
    setCurrentWidget(pConfigurationWidget); // next window (creator)

    // if accepted -> send signal with configuration
    connect(pConfigurationWidget, &CreationDialog::AcceptedConfiguration, this, &LaunchWidget::AcceptedConfiguration);
}
