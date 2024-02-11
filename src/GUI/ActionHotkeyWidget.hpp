#pragma once
#include <QLabel>
#include <QTimer>
#include <QPushButton>

class ActionHotkeyWidget : public QWidget
{
    Q_OBJECT

private: // Data
    QString     hotkey;
    QLabel      actionNameLabel;
    QLabel      hotkeyLabel;
    QLabel      image;
    QPushButton newHotkeyButton;
    QTimer      signalTimer;
    int         timerMseconds;

protected: // Methods
    void keyPressEvent(QKeyEvent*   event) override;
    void focusOutEvent(QFocusEvent* event) override;
public:
    ActionHotkeyWidget(const QString& actionName,
                       const QString& hotkeyStr,
                       const QString& iconName,
                       QWidget* parent = nullptr);
    QString GetActionName() const;
    QString GetHotkey() const;
    void    HighlightKey(bool collision);

signals:
    void SignalRepeatNewHotkey();
    void HotkeyChanged(QString hotkey);
private slots:
    void OnNewHotkeyPressed();
};
