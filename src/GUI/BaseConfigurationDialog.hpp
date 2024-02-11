#pragma once
#include <QDialog>
#include <QVariant>
#include <QButtonGroup>
#include <QDialogButtonBox>

class BaseConfigurationDialog : public QDialog
{
    Q_OBJECT
protected: // Data
    QButtonGroup     buttonsGroup;
    QDialogButtonBox dialogButtons;

public: // Methods
    BaseConfigurationDialog(QWidget* parent = nullptr);
protected:
    // Create configuration data for editor creation.
    virtual QVariant CreateConfigurationData() = 0;

signals:
    void AcceptedConfiguration(QVariant configuration);
};
