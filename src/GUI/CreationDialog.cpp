#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QPixmap>
#include <QCheckBox>
#include <QTranslator>

#include "../Logger.hpp"
#include "../Registry.hpp"
#include "CreationDialog.hpp"

CreationDialog::CreationDialog(QWidget* parent) : QDialog(parent)
{
    QHBoxLayout*  ltOkAndCancel   = new QHBoxLayout();
    QPushButton*  btnOk           = new QPushButton(tr("START"));
    QPushButton*  btnCancel       = new QPushButton(tr("BACK"));
    QHBoxLayout*  ltBtnOk         = new QHBoxLayout();
    QHBoxLayout*  ltBtnCancel     = new QHBoxLayout();

    btnOk->setObjectName("btnOk");
    btnOk->setFixedWidth(80);
    ltBtnOk->setAlignment(Qt::Alignment::enum_type::AlignRight);
    ltBtnOk->addWidget(btnOk);
    btnCancel->setObjectName("btnCancel");
    btnCancel->setFixedWidth(80);
    ltBtnCancel->setAlignment(Qt::Alignment::enum_type::AlignLeft);
    ltBtnCancel->addWidget(btnCancel);
    ltOkAndCancel->addLayout(ltBtnOk);
    ltOkAndCancel->addLayout(ltBtnCancel);

    connect(btnOk,     &QPushButton::clicked, this, [=, this] { emit btnStartClicked(); });
    connect(btnCancel, &QPushButton::clicked, this, [=, this] { emit btnBackClicked(); });

    // configure game buttons
    QRadioButton* rbxGenerals = new QRadioButton(Registry::ToQString(Registry::Games::Generals));
    rbxGenerals->setDisabled(true);
    QFont rbxGeneralsFont = rbxGenerals->font();
    rbxGeneralsFont.setStrikeOut(true);
    rbxGenerals->setFont(rbxGeneralsFont);

    QRadioButton* rbxZeroHour = new QRadioButton(Registry::ToQString(Registry::Games::GeneralsZeroHour));

    rbxZeroHour->setChecked(true);
    QVBoxLayout* ltChoiseGame = new QVBoxLayout();
    ltChoiseGame->addWidget(rbxGenerals);
    ltChoiseGame->addWidget(rbxZeroHour);

    // configure save option
    QCheckBox* chkSaveToGame = new QCheckBox();
    chkSaveToGame->setText(tr("Save hotkeys dirrectly to the game."));

    // configure dialog view
    QVBoxLayout* ltMainBlock = new QVBoxLayout();
    ltMainBlock->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    ltMainBlock->addStretch(5);
    ltMainBlock->addLayout(ltChoiseGame);
    ltMainBlock->addStretch(2);
    ltMainBlock->addWidget(chkSaveToGame);
    ltMainBlock->addStretch(5);
    ltMainBlock->addLayout(ltOkAndCancel);
    ltMainBlock->addStretch(1);
    setLayout(ltMainBlock);
}
