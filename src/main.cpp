#include "gui/mainwindow.hpp"
#include <QApplication>
#include <QDebug>

#include <QByteArray>
#include <iostream>
// #include <QDir>
// #include <QLibrary>

// #include "windows.h"

int main(int argc, char *argv[])
{
	// setlocale(LC_ALL, "");
	// std::cout << "123" << QByteArray(123, 'c').toStdString() << std::endl;
	// qDebug() << "!!!";
	QApplication a(argc, argv);
	// SetDllDirectory("G:\\Special_dir\\Projects\\GZHHotkeysEditor\\build\\src\\deploy");
	// QCoreApplication::instance()->addLibraryPath("deploy");
	// qDebug() << QDir((QDir(a.applicationDirPath()).absolutePath() + "\\deploy")).absolutePath();
	// QCoreApplication::addLibraryPath(QDir((QDir(a.applicationDirPath()).absolutePath() + "\\deploy")).absolutePath());
	// QLibrary ml;
	// ml.setFileName(QDir((QDir(a.applicationDirPath()).absolutePath() + "\\deploy\\Qt5Core.dll")).absolutePath());
	// ml.load();
	MainWindow w;
	// qDebug() << "!!!";
	w.show();
	// qDebug() << "???";
	// std::cout << "123" << std::endl;
	return a.exec();
}
