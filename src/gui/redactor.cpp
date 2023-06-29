#include "redactor.hpp"
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>
#include <QLabel>
#include <QPushButton>

Redactor::Redactor(Config::Games game, bool saveToGame, QWidget *parent)
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
	for(int i = 0; i < 10; i++)
		mainL->addLayout(newHotkey(QString("action_%1").arg(i+1),
								   QString("hotkey_%1").arg(i+1)));
	hotkeysWidget->setLayout(mainL);
	setCentralWidget(hotkeysWidget);
}

QHBoxLayout* Redactor::newHotkey(const QString& action, const QString& hotkey) const
{
	QLabel* keyActionLb = new QLabel(action);
	QLabel* hotkeyLb = new QLabel(hotkey);
	hotkeyLb->setStyleSheet("background-color: gray");
	QPushButton* newHotkeyB = new QPushButton("+");
	QHBoxLayout* hotkeyL = new QHBoxLayout();
	hotkeyL->setAlignment(Qt::AlignTop);
	hotkeyL->addWidget(keyActionLb);
	hotkeyL->addWidget(hotkeyLb);
	hotkeyL->addWidget(newHotkeyB);
	return hotkeyL;
}

Redactor::~Redactor()
{
}
