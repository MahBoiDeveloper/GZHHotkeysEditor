#include "redactor.hpp"
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>

Redactor::Redactor(Config::Games game, bool saveToGame, QWidget *parent)
	: QMainWindow(parent)
{
	QMenu* fm = new QMenu(tr("File"));
	fm->addAction(tr("Special"));
    menuBar()->addMenu(fm);
	menuBar()->addAction(tr("View"));
	QMenu* settingsM = new QMenu(tr("Settings"));
	menuBar()->addMenu(settingsM);
}

Redactor::~Redactor()
{
}
