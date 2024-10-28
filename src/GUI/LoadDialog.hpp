#pragma once
#include "BaseConfigurationDialog.hpp"

class LoadDialog : public BaseConfigurationDialog
{
    Q_OBJECT
private: // Data
    // QButtonGroup buttonsGroup; // Inherited from BaseConfigurationDialog

public: // Methods
    explicit LoadDialog(QWidget *parent = nullptr);
    /// @brief Returns checked config data to initiate editor windows with user preferences.
    QVariant CreateConfigurationData() override;
};
