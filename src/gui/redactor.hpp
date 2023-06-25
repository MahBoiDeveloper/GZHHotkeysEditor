#pragma once
#include <QMainWindow>
#include "configurations.hpp"

class Redactor : public QMainWindow
{
	Q_OBJECT

public:
	Redactor(configurations::Games game, bool saveToGame, QWidget *parent = nullptr);
	~Redactor();
};
