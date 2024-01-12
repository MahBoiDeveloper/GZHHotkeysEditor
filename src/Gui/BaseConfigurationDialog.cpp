#include <QPushButton>
#include "BaseConfigurationDialog.hpp"

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
        }
    );
    connect(&dialogButtons, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);
}
