#include <QApplication>
#include <QDebug>

#include "mainwidget.hpp"
#include "editor/editor.hpp"
#include "initializationWidgets/creatorwidget.hpp"
#include "initializationWidgets/loaderwidget.hpp"

// method for recreating the start widget
StartWidget* MainWidget::initRespawnStartWidget(Config::Languages language)
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
            addWidget(initRespawnStartWidget(language));
        }
    );

    // Buttons effects
    connect(startWidget, &StartWidget::pressed, this,
        // openning create/loader widget
        [=](int index){
            switch (index)
            {
                case 0:
                {
                CreatorWidget* creatorWidget = new CreatorWidget;
                addWidget(creatorWidget);
                setCurrentWidget(creatorWidget); // next window (creator)

                // if accepted -> create redactor with configs and delete other widgets
                connect(creatorWidget, &CreatorWidget::acceptedConfiguration, this,
                    [=](Registry::Games game, bool saveToGame)
                    {
                        for(int i = 0; i < count(); i++) // delete other widgets
                            widget(i)->deleteLater();
                        addWidget(new Editor(game, saveToGame));
                    }
                );

                break;
            }
            case 1: {
                LoaderWidget* loaderWidget = new LoaderWidget;
                addWidget(loaderWidget);
                setCurrentWidget(loaderWidget); // next window (creator)

                // if accepted -> create redactor with configs and delete other widgets
                connect(loaderWidget, &LoaderWidget::acceptedConfiguration, this,
                    [=](const QString& filePath)
                    {
                        qDebug() << filePath;
                        for(int i = 0; i < count(); i++) // delete other widgets
                            widget(i)->deleteLater();
                        addWidget(new Editor(Registry::Games::Generals, false));
                    }
                );

                break;
            }
            default:
                break;
            }
        }
    );

    return startWidget;
}

MainWidget::MainWidget(Config::Languages language, QWidget *parent) : QStackedWidget(parent)
{
    // Application settings
    QFont mainFont(QApplication::font());
    mainFont.setPointSize(11);
    mainFont.setFamily("Consolas");
    QApplication::setFont(mainFont);
    qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text

    // MainWidget settings
    setFixedSize(640, 480);
    addWidget(initRespawnStartWidget(language));
}

void MainWidget::onLanguageChanged(Config::Languages language)
{
    // Delete old translator
    if (translator != nullptr) QCoreApplication::removeTranslator(translator);

    // Create new translator
    if (language != Config::Languages::English)
    {
        translator = new QTranslator;
        translator->load(Config::GetLocaleFromLangEnum(language), "Resources/Translations");
        QCoreApplication::installTranslator(translator);
    }
}
