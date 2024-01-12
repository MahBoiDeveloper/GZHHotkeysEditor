#pragma once

#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVariant>

class BaseConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    BaseConfigurationDialog(QWidget *parent = nullptr);

signals:
    void acceptedConfiguration(QVariant configuration);

protected:
    QButtonGroup buttonsGroup;
    QDialogButtonBox dialogButtons;
    // Create configuration data for editor creation
    virtual QVariant createConfigurationData() = 0;
};
