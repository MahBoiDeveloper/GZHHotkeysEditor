#pragma once

#include <QStackedWidget>
#include <QTranslator>

#include "greeting_widget.hpp"

class StackedLaunchWidget : public QStackedWidget
{
    Q_OBJECT

public:
    StackedLaunchWidget(Config::Languages language, QWidget *parent = nullptr);

private:
    GreetingWidget* createResurgentStartWidget(Config::Languages language = Config::Languages::English);
    void clearStack();

private slots:
    void onLanguageChanged(Config::Languages language);
    void onStartButtonClicked(GreetingWidget::StandartButtons standartButton);
    void onConfigurationAccepted(const QVariant &configuration);

private:
    QTranslator* translator = nullptr;
};