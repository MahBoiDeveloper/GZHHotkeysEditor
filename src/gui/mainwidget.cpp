#include <QApplication>
#include "mainwidget.hpp"
#include "redactor.hpp"
#include "creatorWidget/creatorwidget.hpp"
//#include <QDebug>

// method for recreating the start widget
StartWidget* MainWidget::initRespawnStartWidget(configurations::Languages language)
{
	StartWidget* startWidget = new StartWidget(language);
	connect(startWidget, &StartWidget::languageChanged, this,
		[=](int index){
			configurations::Languages lang = static_cast<configurations::Languages>(index);
			// delete old translator
			if (translator != nullptr)
			{
				QCoreApplication::removeTranslator(translator);
				// there was bug
//				delete translator;
//				translator->deleteLater();
			}
			// create new translator
			if (lang != configurations::Languages::English) {
				translator = new QTranslator;
				translator->load(configurations::langEnumToString(lang), "translations");
				QCoreApplication::installTranslator(translator);
			}
			// recreate StartWidget
			startWidget->deleteLater();
			addWidget(initRespawnStartWidget(lang));
		}
	);

	// buttons effects
	connect(startWidget, &StartWidget::pressed, this,
		[=](int index){
			switch (index) {
			case 0: {
				CreatorWidget* creatorWidget = new CreatorWidget;
				addWidget(creatorWidget);
				setCurrentWidget(creatorWidget); // next window (creator)
				// if accepted -> create redactor with configs and delete other widgets
				connect(creatorWidget, &CreatorWidget::acceptedConfiguration, this,
					[=](configurations::Games game, bool saveToGame){
						for(int i = 0; i < count(); i++) // delete other widgets
							widget(i)->deleteLater();
						addWidget(new Redactor(game, saveToGame));
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

MainWidget::MainWidget(QWidget *parent)
	: QStackedWidget(parent)
{
	// Application settings
	QFont mainFont(QApplication::font());
	mainFont.setPointSize(12);
	QApplication::setFont(mainFont);
	qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text

	// MainWidget settings
	resize(700,500);
	addWidget(initRespawnStartWidget());
}

MainWidget::~MainWidget()
{
}
