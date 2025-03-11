#include <QPushButton>
#include <QStyle>

#include "../ProgramConstants.hpp"
#include "../Convert.hpp"
#include "../Logger.hpp"

#include "ActionHotkeyWidget.hpp"
#include "KeyboardLayout.hpp"

KeyboardLayout::KeyboardLayout(QWidget* parent) : QVBoxLayout(parent)
{
    pFirstLine  = CreateKeysOnKeyboard("QWERTYUIOP");
    pSecondLine = CreateKeysOnKeyboard("ASDFGHJKL");
    pThirdLine  = CreateKeysOnKeyboard("ZXCVBNM");

    QPushButton* btnEmptyButton= new QPushButton();
    btnEmptyButton->setProperty("key", "null");
    btnEmptyButton->setFixedWidth(PROGRAM_CONSTANTS->EMPTY_KEY_WIDTH);
    
    pThirdLine->addWidget(btnEmptyButton);

    pFirstLine->setAlignment(Qt::AlignHCenter);
    pSecondLine->setAlignment(Qt::AlignHCenter);
    pThirdLine->setAlignment(Qt::AlignHCenter);

    addLayout(pFirstLine);
    addLayout(pSecondLine);
    addLayout(pThirdLine);
}

QHBoxLayout* KeyboardLayout::CreateKeysOnKeyboard(const QString& str)
{
    QHBoxLayout* pKeys = new QHBoxLayout();

    for (const QChar& ch : str)
    {
        QPushButton* key = new QPushButton(ch);
        key->setObjectName(ch);
        key->setProperty("key", ch);
        key->setProperty("status", "null");
        key->setFixedWidth(PROGRAM_CONSTANTS->KEYBOARD_KEY_WIDTH);
        pKeys->addWidget(key);
    }

    return pKeys;
}

KeyboardLayout* KeyboardLayout::Nullify()
{
    for (QChar& qc : QString("QWERTYUIOPASDFGHJKLZXCVBNM")) 
    {
        LOGMSG("Search for child with object name : " + qc);
        auto key = this->findChild<QPushButton*>(qc, Qt::FindChildrenRecursively);
        key->setProperty("status", "null");
        key->style()->unpolish(key);
        key->style()->polish(key);
        key->update();
    }

    return this;
}

KeyboardLayout* KeyboardLayout::Update(const QTabWidget& tab, int id)
{
    Nullify();
    auto currTab = tab.findChild<QWidget*>(QString("Layout ") + QString::number(id + 1), Qt::FindChildrenRecursively);
        
    QString accum;
    for (const auto& elem : currTab->findChildren<ActionHotkeyWidget*>(QString(), Qt::FindChildrenRecursively))
        accum += QString(elem->GetHotkey()).toUpper();

    for (const QChar& ch : accum)
    {
        auto key = this->findChild<QPushButton*>(ch, Qt::FindChildrenRecursively);

        if (key == nullptr)
            continue;

        if (accum.count(ch) < 2) key->setProperty("status", "good");
        else                     key->setProperty("status", "bad");

        if (!PROGRAM_CONSTANTS->pSettingsFile->GetAllowedKeys().contains(Convert::ToQtKey(ch)))
            key->setProperty("status", "bad");
        
        key->style()->unpolish(key);
        key->style()->polish(key);
        key->update();
    }

    return this;
}
