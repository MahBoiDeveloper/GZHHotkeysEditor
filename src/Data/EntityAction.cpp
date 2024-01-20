#include "EntityAction.hpp"

EntityAction::EntityAction(const QString& name, const QString& iconName, const QString& hotkey)
    : name{name}
    , iconName{iconName}
    , hotkey{hotkey}
{
}

const QString& EntityAction::getName() const
{
    return name;
}

const QString& EntityAction::getIconName() const
{
    return iconName;
}

const QString& EntityAction::getHotkey() const
{
    return hotkey;
}

void EntityAction::setHotkey(const QString& newHotkey)
{
    hotkey = newHotkey;
}
