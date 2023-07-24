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
    static QImage decodeWebpIcon(const QString& iconName);

public slots:
    void onAbout() const;
};
