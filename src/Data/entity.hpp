#pragma once
#include <QVector>
#include "entity_action.hpp"

class Entity
{
public:
    Entity(const QString& name, const QString& ingameName, const QVector<EntityAction>& actions);

    const QString& getName() const;

    const QString& getIngameName() const;

    const QVector<EntityAction>& getActions() const;

private:
    QString name;
    QString ingameName;
    QVector<EntityAction> actions;
};
