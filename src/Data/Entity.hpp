#pragma once

#include <QVector>

#include "EntityAction.hpp"

class Entity
{
public:
    Entity(const QString& name, const QString& iconName, const QVector<EntityAction>& actions);
    const QString& getName() const;
    const QString& getIconName() const;
    const QVector<EntityAction>& getActions() const;

private:
    QString name;
    QString iconName;
    QVector<EntityAction> actions;
};
