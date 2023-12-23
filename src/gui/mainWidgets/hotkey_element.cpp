#include <QHBoxLayout>
#include <QKeyEvent>
#include <QFile>
#include <QDebug>

#include "hotkey_element.hpp"
#include <../config.hpp>

HotkeyElement::HotkeyElement(const QString& actionName,
                             const QString& hotkeyStr,
                             const QString& iconName,
                             QWidget* parent)
    : QWidget(parent)
    , hotkey{hotkeyStr}
    , actionNameLabel(actionName)
    , hotkeyLabel(hotkey)
    , newHotkeyButton{"+"}
{
    connect(&newHotkeyButton, &QPushButton::pressed, this, &HotkeyElement::onNewHotkeyPressed);

    QLabel* imageLb = new QLabel;
    imageLb->setPixmap(QPixmap::fromImage(Config::decodeWebpIcon(iconName)));

    // hotkey
    hotkeyLabel.setAlignment(Qt::AlignCenter);
    hotkeyLabel.setStyleSheet("padding-left: 30px; padding-right: 30px; background-color: gray");
    // square button size
    newHotkeyButton.setFixedSize(newHotkeyButton.sizeHint().height(), newHotkeyButton.sizeHint().height());

    QHBoxLayout* mainL = new QHBoxLayout(this);
    mainL->setAlignment(Qt::AlignTop);
    mainL->addWidget(imageLb);
    mainL->addWidget(&actionNameLabel);
    mainL->setStretch(0, 1);
    mainL->addWidget(&hotkeyLabel);
    mainL->addWidget(&newHotkeyButton);
    setLayout(mainL);
}

QString HotkeyElement::getActionName() const
{
    return actionNameLabel.text();
}

QString HotkeyElement::getHotkey() const
{
    return hotkeyLabel.text();
}

void HotkeyElement::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (key >= availableKeys.first && key <= availableKeys.second)
    {
        hotkey = QKeySequence(key).toString();
        // return focus to button
        newHotkeyButton.setFocus();
    }
    else
    {
        qDebug() << "This key is not allowed";
    }
    QWidget::keyPressEvent(event);
}

void HotkeyElement::focusOutEvent(QFocusEvent* event)
{
    // unset decoration
    hotkeyLabel.setFont(QFont());
    hotkeyLabel.setPalette(QPalette());

    hotkeyLabel.setText(hotkey);
    QWidget::focusOutEvent(event);
}

void HotkeyElement::onNewHotkeyPressed()
{
    // decoration
    hotkeyLabel.setText(tr("Press any key..."));
    QFont f(hotkeyLabel.font());
    f.setItalic(true);
    hotkeyLabel.setFont(f);
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::GlobalColor::cyan);
    hotkeyLabel.setPalette(p);
    setFocus(); // set focus to current action
}
