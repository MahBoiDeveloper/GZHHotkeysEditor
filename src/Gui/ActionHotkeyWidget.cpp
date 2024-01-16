#include <QKeyEvent>
#include <QDebug>

#include "GUIConfig.hpp"
#include "ActionHotkeyWidget.hpp"

ActionHotkeyWidget::ActionHotkeyWidget(const QString& actionName,
                                       const QString& hotkeyStr,
                                       const QString& iconName,
                                       QWidget* parent)
    : QWidget{parent}
    , hotkey{hotkeyStr}
    , actionNameLabel{actionName}
    , hotkeyLabel{hotkey}
    , newHotkeyButton{"+"}
{
    connect(&newHotkeyButton, &QPushButton::pressed, this, &ActionHotkeyWidget::OnNewHotkeyPressed);

    // Signal timer settings
    signalTimer.setSingleShot(true);
    connect(&signalTimer, &QTimer::timeout, this, &ActionHotkeyWidget::signalRepeatNewHotkey);

    QLabel* imageLb = new QLabel;
    imageLb->setPixmap(QPixmap::fromImage(GUIConfig::decodeWebpIcon(iconName)));

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
    // Move action name label to left
    mainL->setStretch(1, 1);
    mainL->addWidget(&hotkeyLabel);
    mainL->addWidget(&newHotkeyButton);
    setLayout(mainL);
}

QString ActionHotkeyWidget::GetActionName() const
{
    return actionNameLabel.text();
}

QString ActionHotkeyWidget::GetHotkey() const
{
    return hotkeyLabel.text();
}

void ActionHotkeyWidget::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (key >= availableKeys.first && key <= availableKeys.second)
    {
        // Set new text
        hotkey = QKeySequence(key).toString();

        // If the key is correct -> disconnect the input error reset signal
        disconnect(this, &ActionHotkeyWidget::signalRepeatNewHotkey, this, &ActionHotkeyWidget::OnNewHotkeyPressed);

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

void ActionHotkeyWidget::focusOutEvent(QFocusEvent* event)
{
    // Unset decoration
    hotkeyLabel.setFont(QFont());
    hotkeyLabel.setPalette(QPalette());
    hotkeyLabel.setText(hotkey);

    // Stop timer
    signalTimer.stop();

    QWidget::focusOutEvent(event);
}

void ActionHotkeyWidget::OnNewHotkeyPressed()
{
    // Reconnect the input error reset signal
    disconnect(this, &ActionHotkeyWidget::signalRepeatNewHotkey, this, &ActionHotkeyWidget::OnNewHotkeyPressed);
    connect(this, &ActionHotkeyWidget::signalRepeatNewHotkey, this, &ActionHotkeyWidget::OnNewHotkeyPressed);

    // Decorate
    hotkeyLabel.setText(tr("Press latin key..."));
    QFont f(hotkeyLabel.font());
    f.setItalic(true);
    hotkeyLabel.setFont(f);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::GlobalColor::blue);
    hotkeyLabel.setPalette(palette);

    // Set focus on hotkey element
    setFocus();
}
