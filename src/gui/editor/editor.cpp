#include "editor.hpp"
#include "hotkeyelement.h"
#include <QDebug>
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>
#include <QScrollArea>

Editor::Editor(Helper::Games game, bool saveToGame, QWidget *parent)
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
										   QString("hotkey_%1").arg(i+1),
										   QString("sources/icons/Gen1_Hacker_Icons.webp")));
	hotkeysWidget->setLayout(mainL);

	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidget(hotkeysWidget);

	setCentralWidget(scrollArea);
}
