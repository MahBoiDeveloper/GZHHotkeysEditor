#pragma once
#include <QMainWindow>

class Redactor : public QMainWindow
{
	Q_OBJECT

public:
	Redactor(QWidget *parent = nullptr);
	~Redactor();
};
