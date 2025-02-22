#pragma once
#include <QWidget>
#include "../ProgramConstants.hpp"

class GreetingWindow : public QWidget
{
    Q_OBJECT
public: // Data
    enum class StandartButtons
    {
        NewProject,
        LoadProject
    };

public: // Methods
    GreetingWindow(QWidget* parent = nullptr);
private:
    int GetGreetingTextAverageSize(const QString& text) const;

signals:
    void pressed(GreetingWindow::StandartButtons standartButton);
    void languageChanged(int index);
    void btnSettings_Clicked();
};
