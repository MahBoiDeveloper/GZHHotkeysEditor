#pragma once

#include <QDialog>
#include <QButtonGroup>
#include <QCheckBox>
#include "configurations.hpp"

class CreatorWidget : public QDialog
{
	Q_OBJECT
	QButtonGroup groupB;
	QCheckBox saveToGameBox;
public:
	CreatorWidget(QWidget *parent = nullptr);
signals:
	void acceptedConfiguration(configurations::Games game, bool saveToGame);
};
