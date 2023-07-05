#pragma once

#include <QLabel>
#include <QPushButton>

class HotkeyElement : public QWidget
{
	Q_OBJECT
private:
	QLabel actionNameLb;
	QLabel hotkeyLb;
	QPushButton newHotkeyB;

protected:
	void keyPressEvent(QKeyEvent* event) override;

public:
	HotkeyElement(const QString& actionName, const QString& hotkeyStr, QWidget* parent = nullptr);
	QString getActionName() const;
	QString getHotkey() const;
};
