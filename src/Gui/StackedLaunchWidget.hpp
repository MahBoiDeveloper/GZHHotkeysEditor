#pragma once
#include <QTranslator>
#include <QStackedWidget>
#include "GreetingWidget.hpp"

class LaunchWidget : public QStackedWidget
{
    Q_OBJECT
private: // Data
    QTranslator*       pTranslator    = nullptr;
    GreetingWidget*    pStartWidget   = nullptr;

private: // Methods
    void SetTranslator(Config::Languages language);
    void UpdateConnectionsToSignals();
public:
    LaunchWidget(Config::Languages language, QWidget* parent = nullptr);

private slots:
    void OnChangeLanguage(int intLngIndex);
    void OnStartButtonClicked(GreetingWidget::StandartButtons standartButton);
signals:
    void AcceptedConfiguration(const QVariant& configuration);
};
