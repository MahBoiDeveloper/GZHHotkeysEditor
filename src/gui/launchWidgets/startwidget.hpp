#pragma once

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>

#include "../config.hpp"

class StartWidget : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup mainButtons;

public:
    enum class Buttons {
        NewProject = 0,
        LoadProject
    };

private:
    QPushButton* CreateButton(const QString& qstrButtonName) const;

public:
    StartWidget(Config::Languages language = Config::Languages::English, QWidget *parent = nullptr);

signals:
    void pressed(StartWidget::Buttons button);
    void languageChanged(int index);
};
