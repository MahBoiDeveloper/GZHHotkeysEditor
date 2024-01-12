#pragma once

#include <QTranslator>
#include <QStackedWidget>

#include "greeting_widget.hpp"

class StackedLaunchWidget : public QStackedWidget
{
    Q_OBJECT

public:
    StackedLaunchWidget(Config::Languages language, QWidget *parent = nullptr);

signals:
    void acceptedConfiguration(const QVariant &configuration);

private:
    void SetTranslator(Config::Languages language);
    void UpdateConnectionsToSignals();

private slots:
    void OnChangeLanguage(int intLngIndex);
    void OnStartButtonClicked(GreetingWidget::StandartButtons standartButton);

private:
    QTranslator*       pTranslator    = nullptr;
    GreetingWidget*    pStartWidget   = nullptr;
};
