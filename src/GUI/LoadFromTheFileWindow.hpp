#pragma once
#include <QWidget>

class LoadFromTheFileWindow : public QWidget
{
    Q_OBJECT
public: // Methods
    LoadFromTheFileWindow(QWidget *parent = nullptr);
signals:
    void btnBackClicked();
    void btnStartClicked();
};
