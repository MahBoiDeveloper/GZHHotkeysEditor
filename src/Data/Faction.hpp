#pragma once
#include <QMap>
#include "../config.hpp"
#include "entity.hpp"

class Faction
{
public:
    Faction(const QString& shortName, const QString& displayName, const QString& displayNameDesctiontion);
    void addEntities(Config::Entities entityType, const QVector<Entity>& newEntities);

    const QString& getShortName() const;

    const QString& getDisplayName() const;

    const QString& getDisplayNameDesctiontion() const;

    const QMap<Config::Entities, QVector<Entity>>& getEntities() const;

    QVector<Entity> getEntitiesByType(Config::Entities entityType);


private:
    QString shortName;
    QString displayName;
    QString displayNameDesctiontion;
    QMap<Config::Entities, QVector<Entity>> entities;
};
