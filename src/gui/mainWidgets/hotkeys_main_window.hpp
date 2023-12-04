#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QDialog* aboutDialog = nullptr;

public:
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

public slots:
    void onAbout();
};
