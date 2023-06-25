#include "gui/mainwidget.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	// setlocale(LC_ALL, "");
	QApplication a(argc, argv);
	MainWidget w;
	w.show();
	return a.exec();
}
