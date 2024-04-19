#include <QPushButton>
#include "BaseConfigurationDialog.hpp"

BaseConfigurationDialog::BaseConfigurationDialog(QWidget* parent) : QDialog(parent)
{
    // configure dialog buttons
    dialogButtons.setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dialogButtons.button(QDialogButtonBox::Ok)->setText(tr("Configure"));
    dialogButtons.button(QDialogButtonBox::Cancel)->setText(tr("Back"));
    dialogButtons.setContentsMargins(0, 0, 0, 30);

    // emit accepted configurations
    connect(&dialogButtons, &QDialogButtonBox::accepted, this, [=]()
    {
        emit AcceptedConfiguration(CreateConfigurationData());
    });

    connect(&dialogButtons, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);
}
