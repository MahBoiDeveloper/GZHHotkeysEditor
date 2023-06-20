#include "gui/mainwidget.hpp"
#include <QApplication>
// #include <QDebug>

int main(int argc, char *argv[])
{
	// setlocale(LC_ALL, "");
	// qDebug() << "!!!";
	QApplication a(argc, argv);
	MainWidget w;
	w.show();
	return a.exec();
}
