#pragma once
#include <QStackedWidget>
#include <QTranslator>
#include "startWidget/startwidget.hpp"

class MainWidget : public QStackedWidget
{
	Q_OBJECT
private:
	QTranslator* translator = nullptr;

	StartWidget* initRespawnStartWidget(configurations::Languages language = configurations::Languages::English);

public:
	MainWidget(QWidget *parent = nullptr);
	~MainWidget();
};
