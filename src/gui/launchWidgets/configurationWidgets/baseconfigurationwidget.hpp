#pragma once

#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVariant>

class BaseConfigurationWidget : public QDialog
{
    Q_OBJECT
protected:
    QButtonGroup groupB;
    QDialogButtonBox dialogButtons;
    // Create configuration data for editor creation
    virtual QVariant createConfigurationData() = 0;
public:
    BaseConfigurationWidget(QWidget *parent = nullptr);

signals:
    void acceptedConfiguration(QVariant configuration);
};
