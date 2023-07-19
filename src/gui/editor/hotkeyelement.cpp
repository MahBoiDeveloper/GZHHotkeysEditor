#include "hotkeyelement.h"
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QFile>
#include "webp/decode.h"

#include <QDebug>

void HotkeyElement::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (key >= Qt::Key_A && key <= Qt::Key_Z) {
        hotkeyLb.setText(QKeySequence(key).toString());
        // unset decoration
        hotkeyLb.setFont(QFont());
        hotkeyLb.setPalette(QPalette());
        // return focus to parent
        parentWidget()->setFocus();
    } else
        qDebug() << "no";
    QWidget::keyPressEvent(event);
}

HotkeyElement::HotkeyElement(const QString& actionName,
                             const QString& hotkeyStr,
                             const QString& imagePath,
                             QWidget* parent)
    : QWidget(parent)
    , actionNameLb(actionName)
    , hotkeyLb(hotkeyStr)
{
    // image
    QFile imageFile(imagePath);
    if(!imageFile.open(QIODevice::ReadOnly))
    {
        imageFile.setFileName(HotkeyElement::imageNotAllowedPath);
        if(!imageFile.open(QIODevice::ReadOnly))
            qDebug() << "Not read.";
    }
    QByteArray imageData = imageFile.readAll();
    imageFile.close();
    int w,h;
    uint8_t* decodedImage = WebPDecodeRGBA((const uint8_t*)imageData.constData(), imageData.size(), &w, &h);
    QImage image(decodedImage, w, h, QImage::Format_RGBA8888);
    QLabel* imageLb = new QLabel;
    imageLb->setPixmap(QPixmap::fromImage(image));

    // hotkey
    hotkeyLb.setAlignment(Qt::AlignCenter);
    hotkeyLb.setStyleSheet("padding-left: 30px; padding-right: 30px; background-color: gray");
    QPushButton* newHotkeyB = new QPushButton("+");
    // square button
    newHotkeyB->setFixedSize(newHotkeyB->sizeHint().height(), newHotkeyB->sizeHint().height());
    // suggest entering a hotkey
    connect(newHotkeyB, &QPushButton::pressed, this,
            [this]()
            {
                // decoration
                hotkeyLb.setText(tr("Press any key..."));
                QFont f(hotkeyLb.font());
                f.setItalic(true);
                hotkeyLb.setFont(f);
                QPalette p;
                p.setColor(QPalette::WindowText, Qt::GlobalColor::cyan);
                hotkeyLb.setPalette(p);
                setFocus(); // set focus to current action
            }
    );

    QHBoxLayout* mainL = new QHBoxLayout(this);
    mainL->setAlignment(Qt::AlignTop);
    mainL->addWidget(imageLb);
    mainL->addWidget(&actionNameLb);
    mainL->setStretch(0, 1);
    mainL->addWidget(&hotkeyLb);
    mainL->addWidget(newHotkeyB);
    setLayout(mainL);
}

QString HotkeyElement::getActionName() const
{
    return actionNameLb.text();
}

QString HotkeyElement::getHotkey() const
{
    return hotkeyLb.text();
}
