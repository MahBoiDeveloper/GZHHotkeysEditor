#include "gui/mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <QByteArray>
#include <iostream>

int main(int argc, char *argv[])
{
	// setlocale(LC_ALL, "");
	std::cout << "123" << QByteArray(123, 'c').toStdString() << std::endl;
	qDebug() << "!!!";
	QApplication a(argc, argv);
	MainWindow w;
	// qDebug() << "!!!";
	w.show();
	// qDebug() << "???";
	// std::cout << "123" << std::endl;
	return a.exec();
}
