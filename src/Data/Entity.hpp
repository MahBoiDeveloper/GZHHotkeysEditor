#pragma once

#include <QVector>
#include <QSharedPointer>

#include "EntityAction.hpp"

class Entity
{
public:
    Entity(const QString& name, const QString& iconName, const QVector<QSharedPointer<EntityAction>>& actions);
    const QString& GetName() const;
    const QString& GetIconName() const;
    const QVector<QSharedPointer<EntityAction>>& GetActions() const;

private:
    QString Name;
    QString IconName;
    QVector<QSharedPointer<EntityAction>> Actions;
};
