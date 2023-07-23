#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>

#include "../../Registry.hpp"

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(Registry::Games game, bool saveToGame, QWidget *parent = nullptr);
};
