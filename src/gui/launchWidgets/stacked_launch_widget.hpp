#pragma once

#include <QStackedWidget>
#include <QTranslator>

#include "greeting_widget.hpp"

class StackedLaunchWidget : public QStackedWidget
{
    Q_OBJECT
private:
    QTranslator* translator = nullptr;

private:
    GreetingWidget* createResurgentStartWidget(Config::Languages language = Config::Languages::English);
    void clear();

public:
    StackedLaunchWidget(Config::Languages language, QWidget *parent = nullptr);

private slots:
    void onLanguageChanged(Config::Languages language);
    void onStartButtonClicked(GreetingWidget::Buttons button);
    void onConfigurationAccepted(const QVariant &configuration);
};
