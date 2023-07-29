#pragma once

#include <QStackedWidget>
#include <QTranslator>

#include "initializationWidgets/startwidget.hpp"

class MainWidget : public QStackedWidget
{
    Q_OBJECT
private:
    QTranslator* translator = nullptr;

private:
    StartWidget* createResurgentStartWidget(Config::Languages language = Config::Languages::English);
    void clear();

public:
    MainWidget(Config::Languages language, QWidget *parent = nullptr);

public slots:
    void onLanguageChanged(Config::Languages language);
    void onStartButtonClicked(StartWidget::Buttons button);
};
