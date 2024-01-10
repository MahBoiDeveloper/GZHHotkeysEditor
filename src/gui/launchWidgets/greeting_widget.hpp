#pragma once

#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>

#include "../../config.hpp"

class GreetingWidget : public QWidget
{
    Q_OBJECT

public:
    enum class StandartButtons
    {
        NewProject,
        LoadProject
    };

    GreetingWidget(Config::Languages language = Config::Languages::English, QWidget *parent = nullptr);

signals:
    void pressed(GreetingWidget::StandartButtons standartButton);
    void languageChanged(int index);

private:
    void addStandartButton(GreetingWidget::StandartButtons standartButton, const QString& buttonName);
    QHBoxLayout* createLanguageLayout(Config::Languages language, const QString& labelText) const;
    int getGreetingAverageSize(const QString& text) const;

    QPushButton* CreateButton(const QString& qstrButtonName) const;

private:
    QButtonGroup mainButtons;
};
