#pragma once

#include <QString>

/// @brief class for storing entity action data
class EntityAction
{
public:
    EntityAction(const QString& name, const QString& iconName, const QString& hotkey);
    const QString& getName() const;
    const QString& getIconName() const;
    const QString& getHotkey() const;
    void setHotkey(const QString& newHotkey);

private:
    QString name;
    QString iconName;
    QString hotkey;
};
