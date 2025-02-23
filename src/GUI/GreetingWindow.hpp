#pragma once
#include <QWidget>
#include "../ProgramConstants.hpp"

class GreetingWindow : public QWidget
{
    Q_OBJECT
public: // Methods
    GreetingWindow(QWidget* parent = nullptr);
private:
    int GetGreetingTextAverageSize(const QString& text) const;

signals:
    void btnLoadFromFile_Clicked();
    void btnLoadFromGame_Clicked();
    void languageChanged(int index);
    void btnSettings_Clicked();
};
