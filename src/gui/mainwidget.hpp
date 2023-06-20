#pragma once
#include <QStackedWidget>

class MainWidget : public QStackedWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
	~MainWidget();
};
