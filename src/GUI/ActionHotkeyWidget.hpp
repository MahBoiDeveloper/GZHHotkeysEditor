#pragma once

#include <QLabel>
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
    void highlightKey(bool collision);

signals:
    void signalRepeatNewHotkey();
    void hotkeyChanged(QString hotkey);

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
    int timerMseconds;
};
