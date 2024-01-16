#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>

class ActionHotkeyWidget : public QWidget
{
    Q_OBJECT

private: // Data
    QString hotkey;
    QLabel actionNameLabel;
    QLabel hotkeyLabel;
    QLabel image;
    QPushButton newHotkeyButton;
    QTimer signalTimer;
    QPair<int, int> availableKeys = {Qt::Key_A, Qt::Key_Z};
    int timerMseconds = 1300;

protected: // Methods
    void keyPressEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

public:
    ActionHotkeyWidget(const QString& actionName,
                       const QString& hotkeyStr,
                       const QString& iconName,
                       QWidget* parent = nullptr);
    QString GetActionName() const;
    QString GetHotkey() const;

private slots: // Signals and slots
    void OnNewHotkeyPressed();
signals:
    void signalRepeatNewHotkey();
};
