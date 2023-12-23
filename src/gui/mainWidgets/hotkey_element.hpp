#pragma once

#include <QLabel>
#include <QPushButton>

class HotkeyElement : public QWidget
{
    Q_OBJECT

public:
    HotkeyElement(const QString& actionName,
                  const QString& hotkeyStr,
                  const QString& iconName,
                  QWidget* parent = nullptr);
	QString getActionName() const;
	QString getHotkey() const;

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

    QPair<int, int> availableKeys = {Qt::Key_A, Qt::Key_Z};
};
