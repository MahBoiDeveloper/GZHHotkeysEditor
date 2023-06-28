#pragma once
#include <QMainWindow>
#include "config.hpp"

class Redactor : public QMainWindow
{
	Q_OBJECT

public:
	Redactor(Config::Games game, bool saveToGame, QWidget *parent = nullptr);
	~Redactor();
};
