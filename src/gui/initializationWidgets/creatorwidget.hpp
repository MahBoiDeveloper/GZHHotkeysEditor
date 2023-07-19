#pragma once

#include <QDialog>
#include <QButtonGroup>
#include <QCheckBox>
#include "config.hpp"
#include "../../Helper.hpp"

class CreatorWidget : public QDialog
{
	Q_OBJECT
	QButtonGroup groupB;
	QCheckBox saveToGameBox;
public:
	CreatorWidget(QWidget *parent = nullptr);
signals:
	void acceptedConfiguration(Helper::Games game, bool saveToGame);
};
