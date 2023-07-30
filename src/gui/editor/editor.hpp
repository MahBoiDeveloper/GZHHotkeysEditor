#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>

#include "../../Registry.hpp"

class Editor : public QMainWindow
{
    Q_OBJECT

private:
    QDialog* aboutDialog = nullptr;

public:
    Editor(QVariant configuration, QWidget *parent = nullptr);

public slots:
    void onAbout();
};
