#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>
#include <QStyle>
#include "ActionHotkeyWidget.hpp"
#include "ImageManager.hpp"

ActionHotkeyWidget::ActionHotkeyWidget(const QString& actionName,
                                       const QString& key,
                                       const QString& iconName,
                                       QWidget* parent)
    : QWidget{parent}
    , hotkey{key}
    , actionNameLabel{actionName}
    , btnHotkey{hotkey}
    , signalTimer{}
    , timerMseconds{1300}
{
    // Object name for css
    btnHotkey.setObjectName("btnHotkey");
    btnHotkey.setProperty("unique", false);
    btnHotkey.setMinimumSize(ImageManager::DecodeMissingWebpIcon().size().width() + 15, // Checked for letter W
                             ImageManager::DecodeMissingWebpIcon().size().height());

    connect(&btnHotkey, &QPushButton::pressed, this, &ActionHotkeyWidget::ChangeHotkeyClick);

    // Signal timer settings
    signalTimer.setSingleShot(true);
    connect(&signalTimer, &QTimer::timeout, this, &ActionHotkeyWidget::SignalRepeatNewHotkey);

    QLabel* lblImage = new QLabel();
    lblImage->setPixmap(QPixmap::fromImage(ImageManager::DecodeWebpIcon(iconName)));

    QHBoxLayout* ltMainBlock = new QHBoxLayout{this};
    ltMainBlock->setAlignment(Qt::AlignTop);
    ltMainBlock->addWidget(lblImage);
    ltMainBlock->addWidget(&actionNameLabel);
    // Move action name label to left
    ltMainBlock->setStretch(1, 1);
    ltMainBlock->addWidget(&btnHotkey);
    setLayout(ltMainBlock);
}

QString ActionHotkeyWidget::GetActionName() const { return actionNameLabel.text(); }

QString ActionHotkeyWidget::GetHotkey()     const { return btnHotkey.text(); }

void ActionHotkeyWidget::HighlightKey(bool isKeysMoreThanTwo)
{
    if (isKeysMoreThanTwo)
        btnHotkey.setProperty("unique", false);
    else
        btnHotkey.setProperty("unique", true);

    btnHotkey.style()->unpolish(&btnHotkey);
    btnHotkey.style()->polish(&btnHotkey);

    btnHotkey.update();
}

void ActionHotkeyWidget::keyPressEvent(QKeyEvent* event)
{
    // Skip if there are modifiers
    if (event->modifiers() != Qt::NoModifier)
    {
        QWidget::keyPressEvent(event);
        return;
    }

    int key = event->nativeVirtualKey();
    if (PROGRAM_CONSTANTS->GetAllowedKeys().contains(static_cast<Qt::Key>(key)))
    {
        // Set new text
        hotkey = QKeySequence(key).toString();
        
        // If the key is correct -> disconnect the input error reset signal
        disconnect(this, &ActionHotkeyWidget::SignalRepeatNewHotkey, this, &ActionHotkeyWidget::ChangeHotkeyClick);

        // Return focus to parent
        parentWidget()->setFocus();
    }
    else
    {
        if (!KEYBOARD_KEYS.contains(key))
            btnHotkey.setText(tr("It isn't latin key!"));
        else
            btnHotkey.setText(tr("This key doesn't allowed!"));
        
        // Start the signal timer with a delay of n seconds
        if (signalTimer.isActive())
            signalTimer.stop();

        signalTimer.start(timerMseconds);
    }

    btnHotkey.setProperty("unique", true);
    QWidget::keyPressEvent(event);
}

void ActionHotkeyWidget::focusOutEvent(QFocusEvent* event)
{
    // Unset decoration
    QFont fnt(btnHotkey.font());
    fnt.setItalic(false);
    btnHotkey.setFont(fnt);
    btnHotkey.setText(hotkey);

    emit HotkeyChanged(hotkey);
    if (btnHotkey.property("unique").Bool)
        btnHotkey.setProperty("unique", false);

    // Stop timer
    signalTimer.stop();

    QWidget::focusOutEvent(event);
}

void ActionHotkeyWidget::ChangeHotkeyClick()
{
    // Reconnect the input error reset signal
    disconnect(this, &ActionHotkeyWidget::SignalRepeatNewHotkey, this, &ActionHotkeyWidget::ChangeHotkeyClick);
    connect(this, &ActionHotkeyWidget::SignalRepeatNewHotkey, this, &ActionHotkeyWidget::ChangeHotkeyClick);

    // Decorate
    btnHotkey.setText(tr("Press latin key..."));
    btnHotkey.setProperty("unique", true);
    QFont f(btnHotkey.font());
    f.setItalic(true);
    btnHotkey.setFont(f);

    // Set focus on hotkey element
    setFocus();
}
