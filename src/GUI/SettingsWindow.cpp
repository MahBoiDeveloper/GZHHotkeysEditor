#include <windows.h> // Allows disable console

#include "../Logger.hpp"
#include "../NameOfExt.hpp"
#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow(QWidget* parent) : QWidget(parent)
{
    ltMain                 = new QVBoxLayout(this);
    ltButtons              = new QHBoxLayout();
    ltSettings             = new QVBoxLayout();
    btnBack                = new QPushButton(this);
    btnSave                = new QPushButton(this);
    btnResetAll            = new QPushButton(this);
    chkEnableDebugConsole  = new QCheckBox(this);
    chkEnableDiscordRPC    = new QCheckBox(this);
    chkForceSystemLanguage = new QCheckBox(this);

    chkEnableDebugConsole->setText(tr("Enable debug console"));
    chkEnableDebugConsole->setObjectName(nameof(chkEnableDebugConsole));
    if (settings.IsConsoleEnabled())
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Unchecked);

    chkEnableDiscordRPC->setText(tr("Enable Discord RPC (WIP)"));
    chkEnableDiscordRPC->setObjectName(nameof(chkEnableDiscordRPC));
    if (settings.IsDiscordRPCEnabled())
        chkEnableDiscordRPC->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDiscordRPC->setCheckState(Qt::CheckState::Unchecked);

    // TODO: Make it work later.
    chkForceSystemLanguage->setVisible(false);

    ltSettings->addWidget(chkEnableDebugConsole);
    ltSettings->addWidget(chkEnableDiscordRPC);

    btnSave->setText(tr("SAVE"));
    btnSave->setObjectName(nameof(btnSave));
    connect(btnSave, &QPushButton::clicked, this, &SettingsWindow::BtnSave_Clicked);

    btnResetAll->setText(tr("RESET ALL"));
    btnResetAll->setObjectName(nameof(btnResetAll));
    connect(btnResetAll, &QPushButton::clicked, this, &SettingsWindow::BtnResetAll_Clicked);

    btnBack->setText(tr("BACK"));
    btnBack->setObjectName(nameof(btnBack));
    connect(btnBack, &QPushButton::clicked, this, &SettingsWindow::btnBackClicked);

    ltButtons->addWidget(btnSave);
    ltButtons->addWidget(btnResetAll);
    ltButtons->addWidget(btnBack);

    ltMain->setAlignment(Qt::AlignCenter);
    ltMain->addLayout(ltSettings);
    ltMain->addLayout(ltButtons);
    ltMain->setSpacing(10);
    ltMain->setContentsMargins(160, 120, 160, 120);
    setLayout(ltMain);
}

void SettingsWindow::BtnSave_Clicked() 
{
    settings.SetConsoleStatus(chkEnableDebugConsole->checkState());
    ConsoleWindowStateUpdate(chkEnableDebugConsole->checkState());

    settings.SetDiscordRPCStatus(chkEnableDiscordRPC->checkState());
    DiscordRPCStateUpdate(chkEnableDiscordRPC->checkState());

    settings.Save();
}

void SettingsWindow::BtnResetAll_Clicked() 
{ 
    settings.SetToDefault();

    if (settings.IsConsoleEnabled())
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Unchecked);

    chkEnableDebugConsole->update();
}

void SettingsWindow::ConsoleWindowStateUpdate(const Qt::CheckState& state)
{
    switch (state)
    {
        case Qt::CheckState::Checked:
            ShowWindow(GetConsoleWindow(), SW_SHOW);
            break;
        case Qt::CheckState::Unchecked:
            ShowWindow(GetConsoleWindow(), SW_HIDE);
            break;
    }
}

void SettingsWindow::DiscordRPCStateUpdate(const Qt::CheckState& state)
{
}
