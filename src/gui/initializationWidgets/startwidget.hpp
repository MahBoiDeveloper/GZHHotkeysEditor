#pragma once
#include <QWidget>
//#include "pushbutton.hpp" // outdated
#include "../config.hpp"
#include <QPushButton>
#include <QButtonGroup>

class StartWidget : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup* bg;

private:
    QPushButton* initButton(const QString& name) const;
//    void resizeEvent(QResizeEvent *event) override;   // outdated

public:
    StartWidget(Config::Languages language = Config::Languages::English, QWidget *parent = nullptr);
    ~StartWidget();

signals:
//    void resized(int h);    // outdated signal
    void pressed(int index);
    void languageChanged(int index);
};
