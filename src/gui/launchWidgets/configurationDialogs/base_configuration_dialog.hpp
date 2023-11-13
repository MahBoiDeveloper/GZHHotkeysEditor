#pragma once

#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVariant>

class BaseConfigurationDialog : public QDialog
{
    Q_OBJECT
protected:
    QButtonGroup groupB;
    QDialogButtonBox dialogButtons;
    // Create configuration data for editor creation
    virtual QVariant createConfigurationData() = 0;
public:
    BaseConfigurationDialog(QWidget *parent = nullptr);

signals:
    void acceptedConfiguration(QVariant configuration);
};
