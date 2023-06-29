#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include "config.hpp"

class Redactor : public QMainWindow
{
	Q_OBJECT

public:
	Redactor(Config::Games game, bool saveToGame, QWidget *parent = nullptr);
	QHBoxLayout* newHotkey(const QString& action, const QString& hotkey) const;
	~Redactor();
};
