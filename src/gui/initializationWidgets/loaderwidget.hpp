#pragma once

#include <QButtonGroup>
#include <QDialog>

class LoaderWidget : public QDialog
{
    Q_OBJECT
private:
    QButtonGroup groupB;

public:
    explicit LoaderWidget(QWidget *parent = nullptr);
signals:
    void acceptedConfiguration(const QString& selectedFileName);

};
