#pragma once
#include <QDialog>

class CreationDialog : public QDialog
{
    Q_OBJECT
public: // Methods
    CreationDialog(QWidget* parent = nullptr);
signals:
    void btnBackClicked();
    void btnStartClicked();
};
