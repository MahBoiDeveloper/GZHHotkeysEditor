#include "pushbutton.hpp"
#include <QDebug>
#include <QEvent>
#include <QApplication>
#include <QResizeEvent>

int PushButton::getBaseHeight() const
{
	return baseHeight;
}

void PushButton::setBaseHeight(int newbaseHeight)
{
	baseHeight = newbaseHeight;
}

PushButton::PushButton(const QString& text, QWidget* parent)
	: QPushButton(text, parent)
{
}
