#include <QDialogButtonBox>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QPixmap>
#include <QCheckBox>

#include "../Registry.hpp"
#include "CreationDialog.hpp"

CreationDialog::CreationDialog(QWidget* parent) : QDialog(parent)
{
    QDialogButtonBox* btnbxOkAndCancel = new QDialogButtonBox();
    btnbxOkAndCancel->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    btnbxOkAndCancel->button(QDialogButtonBox::Ok)->setText(tr("START"));
    btnbxOkAndCancel->button(QDialogButtonBox::Cancel)->setText(tr("BACK"));
    connect(btnbxOkAndCancel, &QDialogButtonBox::rejected, this, [=, this] { emit btnBackClicked(); });
    connect(btnbxOkAndCancel, &QDialogButtonBox::accepted, this, [=, this] { emit btnStartClicked(); });

    // configure game buttons
    QRadioButton* rbxGenerals = new QRadioButton(
                QString::fromStdString(Registry::ToString(Registry::Games::Generals)));
    rbxGenerals->setDisabled(true);
    QFont rbxGeneralsFont = rbxGenerals->font();
    rbxGeneralsFont.setStrikeOut(true);
    rbxGenerals->setFont(rbxGeneralsFont);

    QRadioButton* rbxZeroHour = new QRadioButton(
                QString::fromStdString(Registry::ToString(Registry::Games::GeneralsZeroHour)));

    QButtonGroup* btngRadioboxes = new QButtonGroup();

    btngRadioboxes->setExclusive(true);
    rbxZeroHour->setChecked(true);
    btngRadioboxes->addButton(rbxGenerals);
    btngRadioboxes->addButton(rbxZeroHour);
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
    ltMainBlock->addWidget(btnbxOkAndCancel, 0, Qt::AlignCenter);
    ltMainBlock->addStretch(1);
    setLayout(ltMainBlock);
}
