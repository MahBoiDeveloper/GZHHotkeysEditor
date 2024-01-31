#pragma once
#include <QCheckBox>
#include "BaseConfigurationDialog.hpp"

class CreationDialog : public BaseConfigurationDialog
{
    Q_OBJECT

private: // Data
    QCheckBox saveToGameBox;

public: // Method
    CreationDialog(QWidget *parent = nullptr);
    QVariant CreateConfigurationData() override;
};
