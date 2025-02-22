#pragma once
#include <QDialog>

class LoadFromTheGameWindow : public QDialog
{
    Q_OBJECT
public: // Methods
    LoadFromTheGameWindow(QWidget* parent = nullptr);
signals:
    void btnBackClicked();
    void btnStartClicked();
};
