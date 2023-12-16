#include <QApplication>
#include <QDebug>

#include "stacked_launch_widget.hpp"
#include "mainWidgets/hotkeys_main_window.hpp"
#include "configurationDialogs/creation_dialog.hpp"
#include "configurationDialogs/load_dialog.hpp"

StackedLaunchWidget::StackedLaunchWidget(Config::Languages language, QWidget *parent) : QStackedWidget(parent)
{
    // Application settings
    QFont mainFont(QApplication::font());
    mainFont.setPointSize(11);
    mainFont.setFamily("Consolas");
    QApplication::setFont(mainFont);
    qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text
    qApp->setWindowIcon(QIcon(QPixmap::fromImage(Config::decodeWebpIcon("NoImageSmall"))));

    // MainLaunchWidget settings
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);
    addWidget(createResurgentStartWidget(language));
}

// method for recreating the start widget
GreetingWidget* StackedLaunchWidget::createResurgentStartWidget(Config::Languages language)
{
    // Set translator
    onLanguageChanged(language);
    // New StartWidget
    GreetingWidget* startWidget = new GreetingWidget(language);

    // Language changing
    connect(startWidget, &GreetingWidget::languageChanged, this, [=](int languageIndex)
        {
            Config::Languages language = static_cast<Config::Languages>(languageIndex);

            // Change translator
            onLanguageChanged(language);

            // Recreate StartWidget
            startWidget->deleteLater();
            addWidget(createResurgentStartWidget(language));
        }
    );
    // Buttons effects
    connect(startWidget, &GreetingWidget::pressed, this, &StackedLaunchWidget::onStartButtonClicked);

    return startWidget;
}

// delete all widgets
void StackedLaunchWidget::clearStack()
{
    while (count() > 0)
    {
        QWidget* widgetToBeDeleted = currentWidget();
        removeWidget(widgetToBeDeleted);
        widgetToBeDeleted->deleteLater();
    }
}

// Switch to selected language
void StackedLaunchWidget::onLanguageChanged(Config::Languages language)
{
    // Delete old translator
    if (translator != nullptr) QCoreApplication::removeTranslator(translator);

    // Create new translator
    if (language != Config::Languages::English)
    {
        translator = new QTranslator;
        translator->load(Config::GetLocaleFromLangEnum(language), Config::translationsPath);
        QCoreApplication::installTranslator(translator);
    }
}

// Open create/loader widget
void StackedLaunchWidget::onStartButtonClicked(GreetingWidget::StandartButtons standartButton)
{
    BaseConfigurationDialog* configurationWidget;

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
            this, &StackedLaunchWidget::onConfigurationAccepted);
}

// close and create new editor
void StackedLaunchWidget::onConfigurationAccepted(const QVariant& configuration)
{
    clearStack();
    qDebug() << configuration.toString();
    (new HotkeysMainWindow(configuration))->show();
    close();
}