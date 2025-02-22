#pragma once
#include <QWidget>

class LoadFromTheGameWindow : public QWidget
{
    Q_OBJECT
public: // Methods
    LoadFromTheGameWindow(QWidget* parent = nullptr);
signals:
    void btnBackClicked();
    void btnStartClicked();
};
