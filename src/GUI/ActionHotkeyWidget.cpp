#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>
#include "ActionHotkeyWidget.hpp"
#include "GUIConfig.hpp"

ActionHotkeyWidget::ActionHotkeyWidget(const QString& actionName,
                                       const QString& hotkeyStr,
                                       const QString& iconName,
                                       QWidget* parent)
    : QWidget{parent}
    , hotkey{hotkeyStr}
    , actionNameLabel{actionName}
    , hotkeyLabel{hotkey}
    , newHotkeyButton{"+"}
    , signalTimer{}
    , timerMseconds{1300}
{
    // Object name for css
    hotkeyLabel.setObjectName("HotkeyLabel");
    hotkeyLabel.setEnabled(false);
    hotkeyLabel.setMinimumSize(GUIConfig::DecodeMissingWebpIcon().size().width() + 15, // Checked for letter W
                               GUIConfig::DecodeMissingWebpIcon().size().height());

    connect(&newHotkeyButton, &QPushButton::pressed, this, &ActionHotkeyWidget::OnNewHotkeyPressed);

    // Signal timer settings
    signalTimer.setSingleShot(true);
    connect(&signalTimer, &QTimer::timeout, this, &ActionHotkeyWidget::SignalRepeatNewHotkey);

    QLabel* imageLb = new QLabel();
    imageLb->setPixmap(QPixmap::fromImage(GUIConfig::DecodeWebpIcon(iconName)));

    // Hotkey label
    hotkeyLabel.setAlignment(Qt::AlignCenter);

    // TODO: doesn't work
    hotkeyLabel.setWindowOpacity(0.7);

    // Square button size
    newHotkeyButton.setFixedSize(newHotkeyButton.sizeHint().height(), newHotkeyButton.sizeHint().height());

    QHBoxLayout* ltMainBlock = new QHBoxLayout{this};
    ltMainBlock->setAlignment(Qt::AlignTop);
    ltMainBlock->addWidget(imageLb);
    ltMainBlock->addWidget(&actionNameLabel);
    // Move action name label to left
    ltMainBlock->setStretch(1, 1);
    ltMainBlock->addWidget(&hotkeyLabel);
    ltMainBlock->addWidget(&newHotkeyButton);
    setLayout(ltMainBlock);
}

QString ActionHotkeyWidget::GetActionName() const
{
    return actionNameLabel.text();
}

QString ActionHotkeyWidget::GetHotkey() const
{
    return hotkeyLabel.text();
}

void ActionHotkeyWidget::HighlightKey(bool collision)
{
    if (collision)
        hotkeyLabel.setEnabled(true);
    else
        hotkeyLabel.setEnabled(false);
}

void ActionHotkeyWidget::keyPressEvent(QKeyEvent* event)
{
    // Skip if there are modifiers
    if (event->modifiers() != Qt::NoModifier)
    {
        QWidget::keyPressEvent(event);
        return;
    }

    int key = event->key();
    if (key >= Config::AVAILABLE_KEYS.first && key <= Config::AVAILABLE_KEYS.second)
    {
        // Set new text
        hotkey = QKeySequence(key).toString();
        hotkeyLabel.setEnabled(false);
        
        // If the key is correct -> disconnect the input error reset signal
        disconnect(this, &ActionHotkeyWidget::SignalRepeatNewHotkey, this, &ActionHotkeyWidget::OnNewHotkeyPressed);

        // Return focus to parent
        parentWidget()->setFocus();
    }
    else
    {
        hotkeyLabel.setText(tr("It isn't latin key..."));
        
        // Start the signal timer with a delay of n seconds
        if (signalTimer.isActive())
            signalTimer.stop();

        signalTimer.start(timerMseconds);
        hotkeyLabel.setEnabled(true);
    }
    QWidget::keyPressEvent(event);
}

void ActionHotkeyWidget::focusOutEvent(QFocusEvent* event)
{
    // Unset decoration
    QFont fnt(hotkeyLabel.font());
    fnt.setItalic(false);
    hotkeyLabel.setFont(fnt);
    hotkeyLabel.setText(hotkey);

    emit HotkeyChanged(hotkey);
    hotkeyLabel.setEnabled(false);

    // Stop timer
    signalTimer.stop();

    QWidget::focusOutEvent(event);
}

void ActionHotkeyWidget::OnNewHotkeyPressed()
{
    // Reconnect the input error reset signal
    disconnect(this, &ActionHotkeyWidget::SignalRepeatNewHotkey, this, &ActionHotkeyWidget::OnNewHotkeyPressed);
    connect(this, &ActionHotkeyWidget::SignalRepeatNewHotkey, this, &ActionHotkeyWidget::OnNewHotkeyPressed);

    // Decorate
    hotkeyLabel.setText(tr("Press latin key..."));
    hotkeyLabel.setEnabled(false);
    QFont f(hotkeyLabel.font());
    f.setItalic(true);
    hotkeyLabel.setFont(f);

    // Set focus on hotkey element
    setFocus();
}
