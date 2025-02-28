#pragma once
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include "../Settings.hpp"

class SettingsWindow final : public QWidget
{
    Q_OBJECT
private: // Data
    Settings settings;

    QVBoxLayout* ltMain                 = nullptr;
    QHBoxLayout* ltButtons              = nullptr;
    QVBoxLayout* ltSettings             = nullptr;
    QPushButton* btnBack                = nullptr;
    QPushButton* btnSave                = nullptr;
    QPushButton* btnResetAll            = nullptr;
    QCheckBox*   chkEnableDebugConsole  = nullptr;
    QCheckBox*   chkEnableDiscordRPC    = nullptr;
    QCheckBox*   chkForceSystemLanguage = nullptr;
public:
private: // Methods
    /// @brief Enable/disable debug console.
    void ConsoleWindowStateUpdate(const Qt::CheckState& state);
    /// @brief Enable/disable Discord RPC integration.
    /// @todo Implement later.
    void DiscordRPCStateUpdate(const Qt::CheckState& state);
private slots:
    void BtnSave_Clicked();
    void BtnResetAll_Clicked();
public:
    SettingsWindow(QWidget* parent = nullptr);
signals:
    void btnBackClicked();
};
