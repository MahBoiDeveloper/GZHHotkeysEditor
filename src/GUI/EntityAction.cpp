#include "EntityAction.hpp"

EntityAction::EntityAction(const QString& name, const QString& iconName, const QString& hotkey)
    : name{name}
    , iconName{iconName}
    , hotkey{hotkey}
{
}

const QString& EntityAction::GetName() const
{
    return name;
}

const QString& EntityAction::GetIconName() const
{
    return iconName;
}

const QString& EntityAction::GetHotkey() const
{
    return hotkey;
}

void EntityAction::SetHotkey(const QString& newHotkey)
{
    hotkey = newHotkey;
}
