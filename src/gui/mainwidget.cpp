#include <QApplication>
#include <QDebug>

#include "mainwidget.hpp"
#include "editor/editor.hpp"
#include "initializationWidgets/creatorwidget.hpp"
#include "initializationWidgets/loaderwidget.hpp"

// method for recreating the start widget
StartWidget* MainWidget::initRespawnStartWidget(Config::Languages language)
{
    StartWidget* startWidget = new StartWidget(language);

    // Language set
    connect(startWidget, &StartWidget::languageChanged, this,
        [=](int index)
        {
            Config::Languages lang = static_cast<Config::Languages>(index);

            // Delete old translator
            if (translator != nullptr) QCoreApplication::removeTranslator(translator);

            // Create new translator
            if (lang != Config::Languages::English)
            {
                translator = new QTranslator;
                translator->load(Config::LangEnumToString(lang), "Resources/Translations");
                QCoreApplication::installTranslator(translator);
            }

            // Recreate StartWidget
            startWidget->deleteLater();
            addWidget(initRespawnStartWidget(lang));
        }
    );

    // Buttons effects
    connect(startWidget, &StartWidget::pressed, this,
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
                    [=](Helper::Games game, bool saveToGame)
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
                        addWidget(new Editor(Helper::Games::Generals, false));
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

MainWidget::MainWidget(QWidget *parent) : QStackedWidget(parent)
{
    // Application settings
    QFont mainFont(QApplication::font());
    mainFont.setPointSize(11);
    mainFont.setFamily("Consolas");
    QApplication::setFont(mainFont);
    qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text

    // MainWidget settings
    setFixedSize(640, 480);
    addWidget(initRespawnStartWidget());
}

MainWidget::~MainWidget()
{
}
