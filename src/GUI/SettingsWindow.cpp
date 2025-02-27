#include <QPushButton>
#include <QVBoxLayout>

#include "../Logger.hpp"
#include "../NameOfExt.hpp"
#include "../Settings.hpp"
#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* ltMain      = new QVBoxLayout(this);
    QHBoxLayout* ltButtons   = new QHBoxLayout(this);
    QPushButton* btnBack     = new QPushButton(this);
    QPushButton* btnSave     = new QPushButton(this);
    QPushButton* btnResetAll = new QPushButton(this);

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

    ltMain->addLayout(ltButtons);
    ltMain->setAlignment(Qt::AlignCenter);
    ltMain->setSpacing(20);
    ltMain->setContentsMargins(160, 120, 160, 120);
    setLayout(ltMain);
}

void SettingsWindow::BtnSave_Clicked() {}
void SettingsWindow::BtnResetAll_Clicked() {}
