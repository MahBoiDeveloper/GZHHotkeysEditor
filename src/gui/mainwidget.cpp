#include <QApplication>
#include <QTranslator>
#include "mainwidget.hpp"
#include "qdebug.h"
#include "redactor.hpp"
#include "startWidget/startwidget.hpp"
#include "creatorWidget/creatorwidget.hpp"
#include "configurations.hpp"

MainWidget::MainWidget(QWidget *parent)
	: QStackedWidget(parent)
{
//	QTranslator* translator = new QTranslator;
//	qDebug() << translator->load("translations/Gui_ru");
//	qApp->installTranslator(translator);

	// Application settings
	QFont mainFont(QApplication::font());
	mainFont.setPointSize(12);
	QApplication::setFont(mainFont);
	qApp->setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text

	// MainWidget settings
	resize(700,500);
	StartWidget* startWidget = new StartWidget;
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
	addWidget(startWidget);
}

MainWidget::~MainWidget()
{
}
