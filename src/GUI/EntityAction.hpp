#pragma once
#include <QString>

/// @brief Class for storing entity action data.
class EntityAction
{
private: // Data
    QString name;
    QString iconName;
    QString hotkey;

public: // Methods
    EntityAction(const QString& name, const QString& iconName, const QString& hotkey);
    const QString& GetName() const;
    const QString& GetIconName() const;
    const QString& GetHotkey() const;
    void SetHotkey(const QString& newHotkey);
};
