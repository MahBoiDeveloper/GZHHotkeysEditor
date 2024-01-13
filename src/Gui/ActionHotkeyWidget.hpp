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
    int timerMseconds = 1700;

public: // Methods
    ActionHotkeyWidget(const QString& actionName,
                       const QString& hotkeyStr,
                       const QString& iconName,
                       QWidget* parent = nullptr);
    QString getActionName() const;
    QString getHotkey() const;
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

signals:
    void signalRepeatNewHotkey();
private slots:
    void onNewHotkeyPressed();
};
