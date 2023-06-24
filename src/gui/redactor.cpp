#include "redactor.hpp"
#include "qdebug.h"
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>

Redactor::Redactor(configurations::Games game, bool saveToGame, QWidget *parent)
	: QMainWindow(parent)
{
	QTranslator* translator = new QTranslator;
	translator->load("translations/Gui_ru");
	QApplication::instance()->installTranslator(translator);

	QMenu* fm = new QMenu(tr("File"));
	fm->addAction(tr("Special"));
    menuBar()->addMenu(fm);
	menuBar()->addAction(tr("View"));
	QMenu* settingsM = new QMenu(tr("Settings"));
	QAction* languageA = new QAction(tr("Language"));
	connect(languageA, &QAction::triggered, this, // doesnt work
		[&](){
			qDebug() << 123;
			QTranslator* translator = new QTranslator;
			translator->load("translations/Gui_ru");
			QApplication::instance()->installTranslator(translator);
			QCoreApplication::installTranslator(translator);
			QApplication::instance()->processEvents();
//			removeEventFilter(translator);
			update();
//			installEventFilter(translator);
		}
	);
	settingsM->addAction(languageA);
	menuBar()->addMenu(settingsM);
}

Redactor::~Redactor()
{
}
