#pragma once

#include "baseconfigurationwidget.hpp"

class LoaderWidget : public BaseConfigurationWidget
{
    Q_OBJECT
private:
    QButtonGroup groupB;

public:
    explicit LoaderWidget(QWidget *parent = nullptr);
    QVariant createConfigurationData() override;
};
