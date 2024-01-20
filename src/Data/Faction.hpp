#pragma once

#include <QMap>

#include "Entity.hpp"
#include "../Config.hpp"

class Faction
{
public:
    Faction(const QString& shortName, const QString& displayName, const QString& displayNameDescription);
    void addEntities(Config::EntitiesTypes entityType, const QVector<Entity>& newEntities);

    const QString& getShortName() const;
    const QString& getDisplayName() const;
    const QString& getDisplayNameDescription() const;
    const QMap<Config::EntitiesTypes, QVector<Entity>>& getEntitiesMap() const;

private:
    QString shortName;
    QString displayName;
    QString displayNameDescription;
    QMap<Config::EntitiesTypes, QVector<Entity>> entities;
};
