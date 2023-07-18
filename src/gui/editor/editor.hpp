#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include "../../Helper.hpp"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(Helper::Games game, bool saveToGame, QWidget *parent = nullptr);
};
