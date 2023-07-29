#include <QApplication>
#include <QDebug>

#include "mainwidget.hpp"
#include "editor/editor.hpp"
#include "initializationWidgets/creatorwidget.hpp"
#include "initializationWidgets/loaderwidget.hpp"

MainWidget::MainWidget(Config::Languages language, QWidget *parent) : QStackedWidget(parent)
{
    // Application settings
    QFont mainFont(QApplication::font());
    mainFont.setPointSize(11);
    mainFont.setFamily("Consolas");
    QApplication::setFont(mainFont);
    qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text

    // MainWidget settings
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    addWidget(createResurgentStartWidget(language));
}

// method for recreating the start widget
StartWidget* MainWidget::createResurgentStartWidget(Config::Languages language)
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
    connect(startWidget, &StartWidget::pressed, this, &MainWidget::onStartButtonClicked);

    return startWidget;
}

// delete all widgets
void MainWidget::clear()
{
    while (count() > 0)
    {
        QWidget* widgetToBeDeleted = currentWidget();
        removeWidget(widgetToBeDeleted);
        widgetToBeDeleted->deleteLater();
    }
}

// Switch to selected language
void MainWidget::onLanguageChanged(Config::Languages language)
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
void MainWidget::onStartButtonClicked(StartWidget::Buttons button)
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
    connect(configurationWidget, &CreatorWidget::acceptedConfiguration, this,
            [=](QVariant configuration)
    {
        clear();
        addWidget(new Editor(Registry::Games::Generals, true));
        qDebug() << configuration.toString();
    }
    );
}
