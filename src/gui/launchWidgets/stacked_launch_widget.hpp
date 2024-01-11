#pragma once

#include <QTranslator>
#include <QStackedWidget>

#include "greeting_widget.hpp"

class StackedLaunchWidget : public QStackedWidget
{
private: // Data
    Q_OBJECT
    QTranslator* translator = nullptr;

public: // Methods
    StackedLaunchWidget(Config::Languages language, QWidget *parent = nullptr);
private:
    GreetingWidget* createResurgentStartWidget(Config::Languages language = Config::Languages::English);
    void clearStack();
private slots:
    void onLanguageChanged(Config::Languages language);
    void onStartButtonClicked(GreetingWidget::StandartButtons standartButton);
    void onConfigurationAccepted(const QVariant &configuration);
};
