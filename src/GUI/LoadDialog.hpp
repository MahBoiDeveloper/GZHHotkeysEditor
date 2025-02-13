#pragma once
#include <QDialog>

class LoadDialog : public QDialog
{
    Q_OBJECT
public: // Methods
    LoadDialog(QWidget *parent = nullptr);
signals:
    void btnBackClicked();
    void btnStartClicked();
};
