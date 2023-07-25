#pragma once

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>

#include "../config.hpp"

class StartWidget : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup* mainButtons;

private:
    QPushButton* CreateButton(const QString& qstrButtonName) const;

public:
    StartWidget(Config::Languages language = Config::Languages::English, QWidget *parent = nullptr);
    ~StartWidget();

signals:
    void pressed(int index);
    void languageChanged(int index);
};
