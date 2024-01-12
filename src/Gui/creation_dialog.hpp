#pragma once
#include <QCheckBox>
#include "base_configuration_dialog.hpp"

class CreationDialog : public BaseConfigurationDialog
{
    Q_OBJECT

private: // Data
    QCheckBox saveToGameBox;

public: // Method
    CreationDialog(QWidget *parent = nullptr);
    QVariant createConfigurationData() override;
};
