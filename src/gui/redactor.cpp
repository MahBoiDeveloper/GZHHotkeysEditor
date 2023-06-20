#include "redactor.hpp"
#include <QMenuBar>

Redactor::Redactor(QWidget *parent)
	: QMainWindow(parent)
{
    QMenu* fm = new QMenu("File");
	fm->addAction("Special");
    menuBar()->addMenu(fm);
    menuBar()->addAction("View");
    menuBar()->addAction("Settings");
}

Redactor::~Redactor()
{
}
