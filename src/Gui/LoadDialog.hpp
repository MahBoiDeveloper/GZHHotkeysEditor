#pragma once

#include "BaseConfigurationDialog.hpp"

class LoadDialog : public BaseConfigurationDialog
{
    Q_OBJECT
private: // Data
    QButtonGroup groupB;

public: // Methods
    explicit LoadDialog(QWidget *parent = nullptr);
    QVariant CreateConfigurationData() override;
};
