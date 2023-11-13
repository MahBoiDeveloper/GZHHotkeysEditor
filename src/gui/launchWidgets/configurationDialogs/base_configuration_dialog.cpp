#include "base_configuration_dialog.hpp"

#include <QPushButton>

BaseConfigurationDialog::BaseConfigurationDialog(QWidget *parent) : QDialog(parent)
{
    // configure dialog buttons
    dialogButtons.setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dialogButtons.button(QDialogButtonBox::Ok)->setText(tr("Configure"));
    dialogButtons.button(QDialogButtonBox::Cancel)->setText(tr("Back"));

    // emit accepted configurations
    connect(&dialogButtons, &QDialogButtonBox::accepted, this, [=]()
        {
            emit acceptedConfiguration(createConfigurationData());
        ;}
    );
    connect(&dialogButtons, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);

    for (auto & button : dialogButtons.buttons())
    {
        button->setStyleSheet("QPushButton { padding-left: 30px; padding-right: 30px; }");
    }
}
