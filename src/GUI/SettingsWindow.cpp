#include <windows.h> // Allows disable console

#include "../Logger.hpp"
#include "../ProgramConstants.hpp"
#include "../Unsorted.hpp"
#include "WindowManager.hpp"
#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow(QWidget* parent) : QWidget(parent)
{
    ltMain                          = new QVBoxLayout();
    ltButtons                       = new QHBoxLayout();
    ltSettings                      = new QHBoxLayout();
    ltLeftColumn                    = new QVBoxLayout();
    ltRightColumn                   = new QVBoxLayout();
    ltLanguage                      = new QHBoxLayout();
    btnBack                         = new QPushButton();
    btnSave                         = new QPushButton();
    btnResetAll                     = new QPushButton();
    chkEnableDebugConsole           = new QCheckBox();
    chkEnableDiscordRPC             = new QCheckBox();
    chkForceSystemLanguageOnStartUp = new QCheckBox();
    lblLanguage                     = new QLabel();
    cmbLanguage                     = new QComboBox();

    chkEnableDebugConsole->setText(tr("Enable debug console"));
    chkEnableDebugConsole->setObjectName(nameof(chkEnableDebugConsole));
    if (PROGRAM_CONSTANTS->pSettingsFile->IsConsoleEnabled())
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Unchecked);

    chkEnableDiscordRPC->setText(tr("Enable Discord RPC (WIP)"));
    chkEnableDiscordRPC->setObjectName(nameof(chkEnableDiscordRPC));
    if (PROGRAM_CONSTANTS->pSettingsFile->IsDiscordRPCEnabled())
        chkEnableDiscordRPC->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDiscordRPC->setCheckState(Qt::CheckState::Unchecked);

    chkForceSystemLanguageOnStartUp->setText(tr("Force editor to use system language on start up"));
    chkForceSystemLanguageOnStartUp->setObjectName(nameof(chkForceSystemLanguageOnStartUp));
    if (PROGRAM_CONSTANTS->pSettingsFile->IsForceSystemLanguageOnStartUpEnabled())
        chkForceSystemLanguageOnStartUp->setCheckState(Qt::CheckState::Checked);
    else
        chkForceSystemLanguageOnStartUp->setCheckState(Qt::CheckState::Unchecked);

    lblLanguage->setText(tr("Language:"));
    lblLanguage->setObjectName(nameof(lblLanguage));
    
    for (int i = 0; i < static_cast<int>(Languages::Count); ++i)
        cmbLanguage->addItem(Unsorted::GetLanguageFullName(static_cast<Languages>(i)));
    cmbLanguage->setCurrentIndex(static_cast<int>(PROGRAM_CONSTANTS->pSettingsFile->GetLanguage()));
    cmbLanguage->setCurrentText(PROGRAM_CONSTANTS->LANGUAGES_STRINGS.value(PROGRAM_CONSTANTS->pSettingsFile->GetLanguage()).second);

    ltLanguage->setAlignment(Qt::AlignLeading);
    ltLanguage->addWidget(lblLanguage);
    ltLanguage->addWidget(cmbLanguage);

    ltLeftColumn->addWidget(chkEnableDebugConsole);
    ltLeftColumn->addWidget(chkEnableDiscordRPC);
    ltLeftColumn->addWidget(chkForceSystemLanguageOnStartUp);
    ltLeftColumn->addLayout(ltLanguage);

    btnSave->setText(tr("SAVE"));
    btnSave->setObjectName(nameof(btnSave));
    connect(btnSave, &QPushButton::clicked, this, &SettingsWindow::BtnSave_Clicked);

    btnResetAll->setText(tr("RESET ALL"));
    btnResetAll->setObjectName(nameof(btnResetAll));
    connect(btnResetAll, &QPushButton::clicked, this, &SettingsWindow::BtnResetAll_Clicked);

    btnBack->setText(tr("BACK"));
    btnBack->setObjectName(nameof(btnBack));
    connect(btnBack, &QPushButton::clicked, this, &SettingsWindow::btnBackClicked);

    ltSettings->addLayout(ltLeftColumn);
    ltSettings->addLayout(ltRightColumn);

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
    PROGRAM_CONSTANTS->pSettingsFile->SetConsoleStatus(chkEnableDebugConsole->checkState());
    ConsoleWindowStateUpdate(chkEnableDebugConsole->checkState());

    PROGRAM_CONSTANTS->pSettingsFile->SetDiscordRPCStatus(chkEnableDiscordRPC->checkState());
    DiscordRPCStateUpdate(chkEnableDiscordRPC->checkState());

    PROGRAM_CONSTANTS->pSettingsFile->SetForceSystemLanguageOnStartUp(chkForceSystemLanguageOnStartUp->checkState());
    
    if (static_cast<Languages>(cmbLanguage->currentIndex()) != PROGRAM_CONSTANTS->pSettingsFile->GetLanguage())
    {
        PROGRAM_CONSTANTS->pSettingsFile->SetLanguage(static_cast<Languages>(cmbLanguage->currentIndex()));
        emit languageChanged();
    }

    PROGRAM_CONSTANTS->pSettingsFile->Save();
}

void SettingsWindow::BtnResetAll_Clicked()
{ 
    PROGRAM_CONSTANTS->pSettingsFile->SetToDefault();

    if (PROGRAM_CONSTANTS->pSettingsFile->IsConsoleEnabled())
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDebugConsole->setCheckState(Qt::CheckState::Unchecked);

    if (PROGRAM_CONSTANTS->pSettingsFile->IsDiscordRPCEnabled())
        chkEnableDiscordRPC->setCheckState(Qt::CheckState::Checked);
    else
        chkEnableDiscordRPC->setCheckState(Qt::CheckState::Unchecked);
    
    if (PROGRAM_CONSTANTS->pSettingsFile->IsForceSystemLanguageOnStartUpEnabled())
        chkForceSystemLanguageOnStartUp->setCheckState(Qt::CheckState::Checked);
    else
        chkForceSystemLanguageOnStartUp->setCheckState(Qt::CheckState::Unchecked);

    chkEnableDebugConsole->update();
    chkEnableDiscordRPC->update();
    chkForceSystemLanguageOnStartUp->update();
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
