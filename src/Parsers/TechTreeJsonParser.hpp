#pragma once

#include <QJsonArray>

#include "../Data/Faction.hpp"
#include "../Config.hpp"

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
