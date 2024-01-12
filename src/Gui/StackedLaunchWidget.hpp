#pragma once
#include <QTranslator>
#include <QStackedWidget>
#include "GreetingWidget.hpp"

class StackedLaunchWidget : public QStackedWidget
{
    Q_OBJECT
private: // Data
    QTranslator*       pTranslator    = nullptr;
    GreetingWidget*    pStartWidget   = nullptr;

private: // Methods
    void SetTranslator(Config::Languages language);
    void UpdateConnectionsToSignals();
public:
    StackedLaunchWidget(Config::Languages language, QWidget *parent = nullptr);

private slots:
    void OnChangeLanguage(int intLngIndex);
    void OnStartButtonClicked(GreetingWidget::StandartButtons standartButton);
signals:
    void acceptedConfiguration(const QVariant &configuration);
};
