#pragma once
#include <QWidget>
#include "../Config.hpp"

class GreetingWidget : public QWidget
{
    Q_OBJECT

public: // Data
    enum class StandartButtons
    {
        NewProject,
        LoadProject
    };

public: // Methods
    GreetingWidget(Config::Languages language = Config::Languages::English, QWidget* parent = nullptr);
private:
    int GetGreetingTextAverageSize(const QString& text) const;

signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);
};
