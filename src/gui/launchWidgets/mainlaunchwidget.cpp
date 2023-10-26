#include <QApplication>
#include <QDebug>

#include "mainlaunchwidget.hpp"
#include "editor/editor.hpp"
#include "configurationWidgets/creatorwidget.hpp"
#include "configurationWidgets/loaderwidget.hpp"

MainLaunchWidget::MainLaunchWidget(Config::Languages language, QWidget *parent) : QStackedWidget(parent)
{
    // Application settings
    QFont mainFont(QApplication::font());
    mainFont.setPointSize(11);
    mainFont.setFamily("Consolas");
    QApplication::setFont(mainFont);
    qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text
    qApp->setWindowIcon(QIcon(QPixmap::fromImage(Config::decodeWebpIcon("default"))));

    // MainLaunchWidget settings
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);
    addWidget(createResurgentStartWidget(language));
}

// method for recreating the start widget
StartWidget* MainLaunchWidget::createResurgentStartWidget(Config::Languages language)
{
    // Set translator
    onLanguageChanged(language);
    // New StartWidget
    StartWidget* startWidget = new StartWidget(language);

    // Setting language
    connect(startWidget, &StartWidget::languageChanged, this,
        [=](int index)
        {
            Config::Languages language = static_cast<Config::Languages>(index);

            // Change translator
            onLanguageChanged(language);

            // Recreate StartWidget
            startWidget->deleteLater();
            addWidget(createResurgentStartWidget(language));
        }
    );
    // Buttons effects
    connect(startWidget, &StartWidget::pressed, this, &MainLaunchWidget::onStartButtonClicked);

    return startWidget;
}

// delete all widgets
void MainLaunchWidget::clear()
{
    while (count() > 0)
    {
        QWidget* widgetToBeDeleted = currentWidget();
        removeWidget(widgetToBeDeleted);
        widgetToBeDeleted->deleteLater();
    }
}

// Switch to selected language
void MainLaunchWidget::onLanguageChanged(Config::Languages language)
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
void MainLaunchWidget::onStartButtonClicked(StartWidget::Buttons button)
{
    BaseConfigurationWidget* configurationWidget;
    switch (button)
    {
        case StartWidget::Buttons::NewProject:
            configurationWidget = new CreatorWidget;
            break;
        case StartWidget::Buttons::LoadProject:
            configurationWidget = new LoaderWidget;
            break;
    }
    addWidget(configurationWidget);
    setCurrentWidget(configurationWidget); // next window (creator)

    // if accepted -> create redactor with configs and delete other widgets
    connect(configurationWidget, &CreatorWidget::acceptedConfiguration, this, &MainLaunchWidget::onConfigurationAccepted);
}

// close and create new editor
void MainLaunchWidget::onConfigurationAccepted(const QVariant& configuration)
{
    clear();
    qDebug() << configuration.toString();
    (new Editor(configuration))->show();
    close();
}
