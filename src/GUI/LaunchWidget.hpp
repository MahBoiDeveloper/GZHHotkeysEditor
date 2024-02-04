#pragma once
#include <QTranslator>
#include <QStackedWidget>
#include "GreetingWidget.hpp"

class LaunchWidget : public QStackedWidget
{
    Q_OBJECT
private: // Data
    QTranslator*    pTranslator  = nullptr;
    GreetingWidget* pStartWidget = nullptr;

private: // Methods
    /// @brief Set common l10n translator for the whole project by language type from enum.
    void SetTranslator(Config::Languages language);
    /// @brief Updates connections with new pointers to the translator and start widget.
    void UpdateConnectionsToSignals();
public:
    LaunchWidget(Config::Languages language, QWidget* parent = nullptr);

private slots:
    /// @brief Change language by its index if language has been changed via select list.
    void OnChangeLanguage(int intLngIndex);
    /// @brief Open create/loader widget if start button has been clicked.
    void OnStartButtonClicked(GreetingWidget::StandartButtons standartButton);
signals:
    /// @brief Returns checked configuration of user preferences.
    void AcceptedConfiguration(const QVariant& configuration);
};
