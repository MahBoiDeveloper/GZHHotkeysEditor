#include <QDebug>
#include <QEvent>
#include <QApplication>
#include <QResizeEvent>

#include "pushbutton.hpp"

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
