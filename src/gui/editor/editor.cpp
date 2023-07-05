#include "editor.hpp"
#include "hotkeyelement.h"
#include <QDebug>
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>

Editor::Editor(Config::Games game, bool saveToGame, QWidget *parent)
	: QMainWindow(parent)
{
	QMenu* fm = new QMenu(tr("File"));
	fm->addAction(tr("Special"));
    menuBar()->addMenu(fm);
	menuBar()->addAction(tr("View"));
	QMenu* settingsM = new QMenu(tr("Settings"));
	menuBar()->addMenu(settingsM);

	QWidget* hotkeysWidget = new QWidget;
	QVBoxLayout* mainL = new QVBoxLayout;
	for(int i = 0; i < 7; i++)
		mainL->addWidget(new HotkeyElement(QString("action_%1").arg(i+1),
										   QString("hotkey_%1").arg(i+1)));
	hotkeysWidget->setLayout(mainL);
	setCentralWidget(hotkeysWidget);
}
