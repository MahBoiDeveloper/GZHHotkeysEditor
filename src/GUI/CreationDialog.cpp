#include <QDialogButtonBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>

#include "../Registry.hpp"
#include "CreationDialog.hpp"

CreationDialog::CreationDialog(QWidget* parent) : BaseConfigurationDialog(parent)
{
    // configure game buttons
    QRadioButton* generalsButton = new QRadioButton(
                QString::fromStdString(Registry::ToString(Registry::Games::Generals)));
    generalsButton->setDisabled(true);

    QRadioButton* zeroHourButton = new QRadioButton(
                QString::fromStdString(Registry::ToString(Registry::Games::GeneralsZeroHour)));

    buttonsGroup.setExclusive(true);
    zeroHourButton->setChecked(true);
    buttonsGroup.addButton(generalsButton);
    buttonsGroup.addButton(zeroHourButton);
    QVBoxLayout* ltChoiseGame = new QVBoxLayout();
    ltChoiseGame->addWidget(generalsButton);
    ltChoiseGame->addWidget(zeroHourButton);

    // configure save option
    saveToGameBox.setText(tr("Save hotkeys dirrectly to the game."));

    // configure dialog view
    QVBoxLayout* ltMainBlock = new QVBoxLayout();
    ltMainBlock->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    ltMainBlock->addStretch(5);
    ltMainBlock->addLayout(ltChoiseGame);
    ltMainBlock->addStretch(2);
    ltMainBlock->addWidget(&saveToGameBox);
    ltMainBlock->addStretch(5);
    ltMainBlock->addWidget(&dialogButtons, 0, Qt::AlignCenter);
    ltMainBlock->addStretch(1);
    setLayout(ltMainBlock);
}

QVariant CreationDialog::CreateConfigurationData()
{
    return QVariant("Creator widget data.");
}
