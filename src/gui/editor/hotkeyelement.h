#pragma once

#include <QLabel>
#include <QPushButton>

class HotkeyElement : public QWidget
{
	Q_OBJECT
private:
	static inline QString imageNotAllowedPath = "sources/icons/NO_IMG_ALLOWED2.webp";
	QLabel actionNameLb;
	QLabel hotkeyLb;
	QLabel image;
	QPushButton newHotkeyB;

protected:
	void keyPressEvent(QKeyEvent* event) override;

public:
	HotkeyElement(const QString& actionName,
				  const QString& hotkeyStr,
				  const QString& imagePath = imageNotAllowedPath,
				  QWidget* parent = nullptr);
	QString getActionName() const;
	QString getHotkey() const;
};
