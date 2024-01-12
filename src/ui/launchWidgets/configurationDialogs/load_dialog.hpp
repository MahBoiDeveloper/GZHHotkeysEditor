#pragma once

#include "base_configuration_dialog.hpp"

class LoadDialog : public BaseConfigurationDialog
{
    Q_OBJECT
private:
    QButtonGroup groupB;

public:
    explicit LoadDialog(QWidget *parent = nullptr);
    QVariant createConfigurationData() override;
};
