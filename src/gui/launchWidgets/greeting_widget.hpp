#pragma once

#include <memory>
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
    std::unique_ptr<QLabel>      lblGreeting;
    std::unique_ptr<QPushButton> btnNewProject;
    std::unique_ptr<QPushButton> btnLoadProject;
    std::unique_ptr<QVBoxLayout> ltButtons;
    std::unique_ptr<QHBoxLayout> ltContent;
    std::unique_ptr<QLabel>      lblLanguage;
    std::unique_ptr<QComboBox>   cmbLangList;
    std::unique_ptr<QHBoxLayout> ltLanguages;
    std::unique_ptr<QVBoxLayout> ltMain;

public: // Methods
    GreetingWidget(Config::Languages language = Config::Languages::English, QWidget* parent = nullptr);
private:
    int  GetGreetingTextAverageSize(const QString& text) const;
signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);
};
