#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include "../../Helper.hpp"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(Helper::GAMES game, bool saveToGame, QWidget *parent = nullptr);
};
