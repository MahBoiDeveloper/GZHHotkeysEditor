#pragma once

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>

#include "../config.hpp"
//#include "pushbutton.hpp" // outdated

class StartWidget : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup* bg;

private:
    QPushButton* CreateButton(const QString& qstrButtonName) const;
    // void resizeEvent(QResizeEvent *event) override;   // outdated

public:
    StartWidget(Config::Languages language = Config::Languages::English, QWidget *parent = nullptr);
    ~StartWidget();

signals:
    void pressed(int index);
    void languageChanged(int index);
};
