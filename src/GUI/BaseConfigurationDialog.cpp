#include <QPushButton>
#include "BaseConfigurationDialog.hpp"

BaseConfigurationDialog::BaseConfigurationDialog(QWidget* parent) : QDialog(parent)
{
    // configure dialog buttons
    dialogButtons.setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dialogButtons.button(QDialogButtonBox::Ok)->setText(tr("CONFIGURE"));
    dialogButtons.button(QDialogButtonBox::Cancel)->setText(tr("BACK"));
    dialogButtons.setContentsMargins(0, 0, 0, 30);

    // emit accepted configurations
    connect(&dialogButtons, &QDialogButtonBox::accepted, this, [=, this]()
    {
        emit acceptConfiguration(CreateConfigurationData());
    });

    connect(&dialogButtons, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);
}
