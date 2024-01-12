#include "EntityAction.hpp"

EntityAction::EntityAction(const QString& name, const QString& csfString)
    : name{name}
    , csfString{csfString}
    , hotkey{/*TODO: read from csf file*/ Qt::Key::Key_0}
{
}

const QString& EntityAction::getName() const
{
    return name;
}

const QString& EntityAction::getCsfString() const
{
    return csfString;
}

Qt::Key EntityAction::getHotkey() const
{
    return hotkey;
}

void EntityAction::setHotkey(Qt::Key newHotkey)
{
    hotkey = newHotkey;
}
