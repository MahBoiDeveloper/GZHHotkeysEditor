#pragma once

#include <QListWidget>

class ListWidgetBuilding : public QListWidget
{
public:
    ListWidgetBuilding(QWidget *parent = nullptr);

private:
    void resizeEvent(QResizeEvent *event) override;

private:
    QSize iconBaseSize;
};
