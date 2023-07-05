#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include "config.hpp"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(Config::Games game, bool saveToGame, QWidget *parent = nullptr);
};
