#pragma once
#include "../../config.hpp"

class GreetingWidget : public QWidget
{
public: // Data
    enum class StandartButtons
    {
        NewProject,
        LoadProject
    };
private:
    Q_OBJECT

public: // Methods
    GreetingWidget(Config::Languages language = Config::Languages::English, QWidget* parent = nullptr);
private:
    int  GetGreetingTextAverageSize(const QString& text) const;
signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);
};
