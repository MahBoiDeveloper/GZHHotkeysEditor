#pragma once

#include <QDialog>
#include <QButtonGroup>
#include <QCheckBox>

#include "../../Registry.hpp"

class CreatorWidget : public QDialog
{
    Q_OBJECT
    QButtonGroup groupB;
    QCheckBox saveToGameBox;
public:
    CreatorWidget(QWidget *parent = nullptr);
signals:
    void acceptedConfiguration(Registry::Games game, bool saveToGame);
};
