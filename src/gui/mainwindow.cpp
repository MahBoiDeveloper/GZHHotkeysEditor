#include "mainwindow.hpp"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setMinimumSize(700,500);
    QMenu* fm = new QMenu("File");
    fm->addAction("Ы");
    menuBar()->addMenu(fm);
    menuBar()->addAction("View");
    menuBar()->addAction("Settings");
}

MainWindow::~MainWindow()
{
}
