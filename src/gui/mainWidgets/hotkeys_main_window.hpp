#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>

#include "../../Registry.hpp"

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QDialog* aboutDialog = nullptr;

public:
    HotkeysMainWindow(QVariant configuration, QWidget *parent = nullptr);

public slots:
    void onAbout();
};
