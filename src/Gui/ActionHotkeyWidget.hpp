#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>

class ActionHotkeyWidget : public QWidget
{
    Q_OBJECT

public:
    ActionHotkeyWidget(const QString& actionName,
                       const QString& hotkeyStr,
                       const QString& iconName,
                       QWidget* parent = nullptr);
    QString getActionName() const;
    QString getHotkey() const;

signals:
    void signalRepeatNewHotkey();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

private slots:
    void onNewHotkeyPressed();

private:
    QString hotkey;
    QLabel actionNameLabel;
    QLabel hotkeyLabel;
    QLabel image;
    QPushButton newHotkeyButton;
    QTimer signalTimer;
    QPair<int, int> availableKeys = {Qt::Key_A, Qt::Key_Z};
    int timerMseconds = 1300;
};
