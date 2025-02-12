#pragma once
#include <QWidget>
#include "../ProgramConstants.hpp"

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
    GreetingWidget(QWidget* parent = nullptr);
private:
    int GetGreetingTextAverageSize(const QString& text) const;

signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);
};
