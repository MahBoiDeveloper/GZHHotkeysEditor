#pragma once

#include "base_configuration_dialog.hpp"

class LoadDialog : public BaseConfigurationDialog
{
    Q_OBJECT
private: // Data
    QButtonGroup groupB;

public: // Methods
    explicit LoadDialog(QWidget *parent = nullptr);
    QVariant createConfigurationData() override;
};
