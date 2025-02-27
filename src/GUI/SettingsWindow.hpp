#pragma once
#include <QWidget>

class SettingsWindow final : public QWidget
{
    Q_OBJECT
private: // Data
public:
private: // Methods
private slots:
    void BtnSave_Clicked();
    void BtnResetAll_Clicked();
public:
    SettingsWindow(QWidget* parent = nullptr);
signals:
    void btnBackClicked();
};
