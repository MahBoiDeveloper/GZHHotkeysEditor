#pragma once
#include <QStackedWidget>
#include <QTranslator>
#include "initializationWidgets/startwidget.hpp"

class MainWidget : public QStackedWidget
{
	Q_OBJECT
private:
	QTranslator* translator = nullptr;

	StartWidget* initRespawnStartWidget(Config::Languages language = Config::Languages::English);

public:
	MainWidget(QWidget *parent = nullptr);
	~MainWidget();
};
