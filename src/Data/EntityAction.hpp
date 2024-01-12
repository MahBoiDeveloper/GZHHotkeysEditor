#pragma once
#include <QString>

/// @brief class for storing building data
class EntityAction
{
public:
    EntityAction(const QString& name, const QString& csfString);
    const QString& getName() const;
    const QString& getCsfString() const;

    Qt::Key getHotkey() const;
    void setHotkey(Qt::Key newHotkey);

private:
    QString name;
    QString csfString;
    Qt::Key hotkey;
};
