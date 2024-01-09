#include "TechTreeJsonParser.hpp"

#include "JSONFile.hpp"

#define FILE JSONFile{Config::techTreeFile}

/// @brief
QVector<Faction> TechTreeJsonParser::GetFactions()
{
    QVector<Faction> factions;

    for (const auto& jsonFaction : FILE.Query(QString("$.TechTree")).toArray())
    {
        QJsonObject factionObject = jsonFaction.toObject();

        QString ShortName               = factionObject.value("ShortName").toString();
        QString DisplayName             = factionObject.value("DisplayName").toString();
        QString DisplayNameDesctiontion = factionObject.value("DisplayNameDesctiontion").toString();

        Faction newFaction{ShortName, DisplayName, DisplayNameDesctiontion};

        newFaction.addEntities(Config::Entities::Buildings, _entitiesFromJsonArray(factionObject.value("Buildings").toArray()));
        newFaction.addEntities(Config::Entities::Infantry, _entitiesFromJsonArray(factionObject.value("Infantry").toArray()));
        newFaction.addEntities(Config::Entities::Vehicles, _entitiesFromJsonArray(factionObject.value("Vehicles").toArray()));
        newFaction.addEntities(Config::Entities::Aircraft, _entitiesFromJsonArray(factionObject.value("Aircraft").toArray()));

        factions.append(newFaction);
    }

    return factions;
}

QVector<Entity> TechTreeJsonParser::getFactionEntities(Config::Entities entity, const QString& factionShortName)
{
    for (const auto& faction : FILE.Query(QString("$.TechTree")).toArray())
    {
        if (factionShortName == faction.toObject().value("ShortName").toString())
        {
            return _entitiesFromJsonArray(faction.toObject().value(Config::ENTITIES_STRINGS.value(entity)).toArray());
        }
    }
    return {};
}

QVector<Entity> TechTreeJsonParser::_entitiesFromJsonArray(const QJsonArray& array)
{
    QVector<Entity> entities;

    for (const auto & jsonEntity : array)
    {
        entities.append(Entity{jsonEntity.toObject().value("Name").toString(),
                                  jsonEntity.toObject().value("IngameName").toString(),
                                  _actionsFromJsonArray(jsonEntity.toObject().value("Actions").toArray())});
    }

    return entities;
}

QVector<EntityAction> TechTreeJsonParser::_actionsFromJsonArray(const QJsonArray& array)
{
    QVector<EntityAction> actions;

    for (const auto & jsonAction : array)
    {
        actions.append(EntityAction{jsonAction.toObject().value("Name").toString(),
                                    jsonAction.toObject().value("CSFString").toString()});
    }

    return actions;
}
