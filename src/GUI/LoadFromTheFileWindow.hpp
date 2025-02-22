#pragma once
#include <QDialog>

class LoadFromTheFileWindow : public QDialog
{
    Q_OBJECT
public: // Methods
    LoadFromTheFileWindow(QWidget *parent = nullptr);
signals:
    void btnBackClicked();
    void btnStartClicked();
};
