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
    void btnLoadFromFileClicked();
    void btnLoadFromGameClicked();
    void languageChanged(int index);
    void btnSettingsClicked();
};
