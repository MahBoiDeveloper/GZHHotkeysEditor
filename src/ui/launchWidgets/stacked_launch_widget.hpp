#pragma once

#include <QTranslator>
#include <QStackedWidget>

#include "../mainWidgets/hotkeys_main_window.hpp"
#include "greeting_widget.hpp"

class StackedLaunchWidget : public QStackedWidget
{
private: // Data
    Q_OBJECT
    QTranslator*       pTranslator    = nullptr;
    GreetingWidget*    pStartWidget   = nullptr;
    HotkeysMainWindow* pHotkeysEditor = nullptr;

public: // Methods
    StackedLaunchWidget(Config::Languages language, QWidget *parent = nullptr);
private:
    void SetTranslator(Config::Languages language);
    void UpdateConnectionsToSignals();
private slots:
    void OnChangeLanguage(int intLngIndex);
    void OnStartButtonClicked(GreetingWidget::StandartButtons standartButton);
    void OnConfigurationAccepted(const QVariant &configuration);
};
