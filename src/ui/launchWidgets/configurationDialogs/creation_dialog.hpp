#pragma once

#include <QCheckBox>

#include "base_configuration_dialog.hpp"

class CreationDialog : public BaseConfigurationDialog
{
    Q_OBJECT
    QCheckBox saveToGameBox;
public:
    CreationDialog(QWidget *parent = nullptr);
    QVariant createConfigurationData() override;
};
