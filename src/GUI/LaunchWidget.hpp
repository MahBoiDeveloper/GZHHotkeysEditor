#pragma once
#include <QStackedWidget>
#include "GreetingWidget.hpp"

class LaunchWidget final : public QStackedWidget
{
    Q_OBJECT
private: // Data
    GreetingWidget* pGreetingWidget = nullptr;

private: // Methods
    /// @brief Connects slots and singals.
    void AttachConnections();
    /// @brief Disconnects slots and signals.
    void DetachConnections();
public:
    LaunchWidget(QWidget* parent = nullptr);

private slots:
    /// @brief Change language by its index if language has been changed via select list.
    void GreetingWidget_LanguageChanged(int intLngIndex);
    /// @brief Open create/loader widget if start button has been clicked.
    void BtnNewProjectOrBtnLoadProject_Clicked(GreetingWidget::StandartButtons standartButton);
    /// @brief Returns checked configuration of user preferences.
    void CreationDialog_AcceptConfiguration(const QVariant& configuration);
};
