#pragma once

#include <QStackedWidget>
#include <QTranslator>

#include "startwidget.hpp"

class MainLaunchWidget : public QStackedWidget
{
    Q_OBJECT
private:
    QTranslator* translator = nullptr;

private:
    StartWidget* createResurgentStartWidget(Config::Languages language = Config::Languages::English);
    void clear();

public:
    MainLaunchWidget(Config::Languages language, QWidget *parent = nullptr);

private slots:
    void onLanguageChanged(Config::Languages language);
    void onStartButtonClicked(StartWidget::Buttons button);
    void onConfigurationAccepted(const QVariant &configuration);
};
