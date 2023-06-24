#include "gui/mainwidget.hpp"
#include <QApplication>
// #include <QDebug>

int main(int argc, char *argv[])
{
	// setlocale(LC_ALL, "");
	// qDebug() << "!!!";
	QApplication a(argc, argv);
	QFont mainFont(QApplication::font());
	mainFont.setPointSize(12);
	QApplication::setFont(mainFont);
	a.setStyleSheet("QPushButton { padding: 10px; }"); // spacing between border and text
	MainWidget w;
	w.show();
	return a.exec();
}
