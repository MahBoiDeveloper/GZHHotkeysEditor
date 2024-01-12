#pragma once

#include <QWidget>

#include "../config.hpp"

class GreetingWidget : public QWidget
{
    Q_OBJECT

public:
    enum class StandartButtons
    {
        NewProject,
        LoadProject
    };

public:
    GreetingWidget(Config::Languages language = Config::Languages::English, QWidget* parent = nullptr);

signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);

private:
    int  GetGreetingTextAverageSize(const QString& text) const;
};
