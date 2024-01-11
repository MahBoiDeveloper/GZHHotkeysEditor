#pragma once

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

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
    QLabel*      lblGreeting    = nullptr;
    QPushButton* btnNewProject  = nullptr;
    QPushButton* btnLoadProject = nullptr;
    QVBoxLayout* ltButtons      = nullptr;
    QHBoxLayout* ltContent      = nullptr;
    QLabel*      lblLanguage    = nullptr;
    QComboBox*   cmbLangList    = nullptr;
    QHBoxLayout* ltLanguages    = nullptr;
    QVBoxLayout* ltMain         = nullptr;

public: // Methods
    GreetingWidget(Config::Languages language = Config::Languages::English, QWidget* parent = nullptr);
private:
    int  GetGreetingTextAverageSize(const QString& text) const;
signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);
};
