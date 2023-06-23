#include "gui/mainwidget.hpp"
#include "CSFparser.hpp"
#include <QApplication>
// #include <QDebug>

int main(int argc, char *argv[])
{
	// setlocale(LC_ALL, "");
	// qDebug() << "!!!";
	QApplication a(argc, argv);
	MainWidget w;
	w.show();
	auto tmp = new CSFparser("..\\..\\src\\csfSamples\\ra2md.csf");
	return a.exec();
}
