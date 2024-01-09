#pragma once

#include <faction.hpp>

#include <QJsonArray>

#include <config.hpp>

class TechTreeJsonParser
{
public: // Methods
    static QVector<Faction> GetFactions();
    static QVector<Entity> getFactionEntities(Config::Entities entity, const QString& factionShortName);

private:
    static QVector<Entity> _entitiesFromJsonArray(const QJsonArray& array);
    static QVector<EntityAction> _actionsFromJsonArray(const QJsonArray& array);
    static QVector<EntityAction> _getEntityActions(const QString& entityName);
};
