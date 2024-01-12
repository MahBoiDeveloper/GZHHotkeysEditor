#include <QKeyEvent>
#include <QDebug>

#include "hotkey_element.hpp"
#include "gui_config.hpp"

HotkeyElement::HotkeyElement(const QString& actionName,
                             const QString& hotkeyStr,
                             const QString& iconName,
                             QWidget* parent)
    : QWidget{parent}
    , hotkey{hotkeyStr}
    , actionNameLabel{actionName}
    , hotkeyLabel{hotkey}
    , newHotkeyButton{"+"}
{
    connect(&newHotkeyButton, &QPushButton::pressed, this, &HotkeyElement::onNewHotkeyPressed);

    // Signal timer settings
    signalTimer.setSingleShot(true);
    connect(&signalTimer, &QTimer::timeout, this, &HotkeyElement::signalRepeatNewHotkey);

    QLabel* imageLb = new QLabel;
    imageLb->setPixmap(QPixmap::fromImage(GuiConfig::decodeWebpIcon(iconName)));

    // Hotkey label
    hotkeyLabel.setAlignment(Qt::AlignCenter);
    hotkeyLabel.setStyleSheet("padding-left: 30px;"
                              "padding-right: 30px;"
                              "background-color: #ABABAB");
    // TODO: doesn't work
    hotkeyLabel.setWindowOpacity(0.7);
    // Square button size
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
        // Set new text
        hotkey = QKeySequence(key).toString();

        // If the key is correct -> disconnect the input error reset signal
        disconnect(this, &HotkeyElement::signalRepeatNewHotkey, this, &HotkeyElement::onNewHotkeyPressed);

        // Return focus to parent
        parentWidget()->setFocus();
    }
    else
    {
        hotkeyLabel.setText(tr("It isn't latin key..."));
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::GlobalColor::red);
        hotkeyLabel.setPalette(palette);

        // Start the signal timer with a delay of n seconds
        if (signalTimer.isActive())
        {
            signalTimer.stop();
        }
        signalTimer.start(timerMseconds);
    }
    QWidget::keyPressEvent(event);
}

void HotkeyElement::focusOutEvent(QFocusEvent* event)
{
    // Unset decoration
    hotkeyLabel.setFont(QFont());
    hotkeyLabel.setPalette(QPalette());
    hotkeyLabel.setText(hotkey);

    // Stop timer
    signalTimer.stop();

    QWidget::focusOutEvent(event);
}

void HotkeyElement::onNewHotkeyPressed()
{
    // Reconnect the input error reset signal
    disconnect(this, &HotkeyElement::signalRepeatNewHotkey, this, &HotkeyElement::onNewHotkeyPressed);
    connect(this, &HotkeyElement::signalRepeatNewHotkey, this, &HotkeyElement::onNewHotkeyPressed);

    // decorate
    hotkeyLabel.setText(tr("Press latin key..."));
    QFont f(hotkeyLabel.font());
    f.setItalic(true);
    hotkeyLabel.setFont(f);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::GlobalColor::blue);
    hotkeyLabel.setPalette(palette);

    // set focus on hotkey element
    setFocus();
}
