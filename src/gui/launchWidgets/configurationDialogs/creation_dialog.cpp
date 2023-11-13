#include <QDialogButtonBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>

#include "creation_dialog.hpp"
#include "../../../Registry.hpp"

CreationDialog::CreationDialog(QWidget *parent) : BaseConfigurationDialog(parent)
{
    // configure game buttons
    QRadioButton* generalsButton = new QRadioButton(
                QString::fromStdString(Registry::ToString(Registry::Games::Generals)));
    generalsButton->setDisabled(true);

    QRadioButton* zeroHourButton = new QRadioButton(
                QString::fromStdString(Registry::ToString(Registry::Games::GeneralsZeroHour)));

    groupB.setExclusive(true);
    zeroHourButton->setChecked(true);
    groupB.addButton(generalsButton);
    groupB.addButton(zeroHourButton);
    QVBoxLayout* choiseL = new QVBoxLayout;
    choiseL->addWidget(generalsButton);
    choiseL->addWidget(zeroHourButton);

    // configure save option
    saveToGameBox.setText(tr("Save hotkeys dirrectly to the game."));

    // configure dialog view
    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    mainL->addStretch(5);
    mainL->addLayout(choiseL);
    mainL->addStretch(2);
    mainL->addWidget(&saveToGameBox);
    mainL->addStretch(5);
    mainL->addWidget(&dialogButtons, 0, Qt::AlignCenter);
    mainL->addStretch(1);
    setLayout(mainL);
}

QVariant CreationDialog::createConfigurationData()
{
    return QVariant("Creator widget data.");
}
