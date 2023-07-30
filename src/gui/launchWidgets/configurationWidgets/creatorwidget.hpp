#pragma once

#include <QCheckBox>

#include "baseconfigurationwidget.hpp"

class CreatorWidget : public BaseConfigurationWidget
{
    Q_OBJECT
    QCheckBox saveToGameBox;
public:
    CreatorWidget(QWidget *parent = nullptr);
    QVariant createConfigurationData() override;
};
