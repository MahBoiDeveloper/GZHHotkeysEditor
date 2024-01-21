#include <QJsonArray>
#include <QJsonObject>

#include "FactionsManager.hpp"
#include "../Parsers/JSONFile.hpp"
#include "../Parsers/CSFParser.hpp"


FactionsManager::FactionsManager(const QString& techTreeFilePath, QObject *parent)
    : QObject{parent}
    , pTechTree{new JSONFile{techTreeFilePath}}
    , Factions{_GetTechTreeFactions()}
{}

const QVector<Faction>& FactionsManager::GetFactions() const
{
    return Factions;
}

const QMap<Config::EntitiesTypes, QVector<Entity>>* FactionsManager::GetFactionEntities(const QString& factionShortName) const
{
    const Faction* const faction = _GetFactionByShortName(factionShortName);

    if (faction == nullptr) return nullptr;

    return &faction->getEntitiesMap();
}

const QVector<EntityAction>* FactionsManager::GetEntityActions(const QString& factionShortName, const QString& entityName) const
{
    const QMap<Config::EntitiesTypes, QVector<Entity>>* const factionEntities = GetFactionEntities(factionShortName);

    if (factionEntities == nullptr) return nullptr;

    for (const auto & currentEntitiesType : *factionEntities)
    {
        for (const auto & entity : currentEntitiesType)
        {
            if (entity.getName() == entityName)
            {
                return &entity.getActions();
            }
        }
    }

    return nullptr;
}

void FactionsManager::SetEntityActionHotkey(const QString& factionShortName,
                                            const QString& entityName,
                                            const QString& actionName,
                                            const QString& hotkey)
{
     QVector<EntityAction>* const entityActions = const_cast<QVector<EntityAction>*>(GetEntityActions(factionShortName, entityName));

    if (entityActions == nullptr) return;

    for (auto & entityAction : *entityActions)
    {
        // Skip if wrong action
        if (entityAction.getName() != actionName) continue;

        entityAction.setHotkey(hotkey);
    }
}

const Faction* FactionsManager::_GetFactionByShortName(const QString& factionShortName) const
{
    for (const auto & faction : Factions)
    {
        if (faction.getShortName() == factionShortName)
        {
            return &faction;
        }
    }
    return nullptr;
}

#pragma region TechTree.json parsing methods
    QVector<Faction> FactionsManager::_GetTechTreeFactions()
    {
        QVector<Faction> factions;

        for (const auto& jsonFaction : pTechTree->Query("$.TechTree").toArray())
        {
            QJsonObject factionObject = jsonFaction.toObject();

            QString ShortName               = factionObject.value("ShortName").toString();
            QString DisplayName             = factionObject.value("DisplayName").toString();
            QString DisplayNameDescription  = factionObject.value("DisplayNameDescription").toString();

            Faction newFaction{ShortName, DisplayName, DisplayNameDescription};

            for (auto it = Config::ENTITIES_STRINGS.cbegin(); it != Config::ENTITIES_STRINGS.cend(); ++it)
            {
                QVector<Entity> entities = _GetEntitiesFromJsonArray(factionObject.value(it.value()).toArray());
                if (!entities.isEmpty())
                {
                    newFaction.addEntities(it.key(), entities);
                }
            }

            factions.append(newFaction);
        }

        return factions;
    }

    QVector<Entity> FactionsManager::_GetTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName)
    {
        for (const auto& faction : pTechTree->Query("$.TechTree").toArray())
        {
            if (factionShortName == faction.toObject().value("ShortName").toString())
            {
                return _GetEntitiesFromJsonArray(faction.toObject().value(Config::ENTITIES_STRINGS.value(entity)).toArray());
            }
        }

        return {};
    }

    QVector<Entity> FactionsManager::_GetEntitiesFromJsonArray(const QJsonArray& array)
    {
        QVector<Entity> entities;

        for (const auto & jsonEntity : array)
        {
            entities.append(Entity{CSFPARSER->GetStringValue(jsonEntity.toObject().value("IngameName").toString()),
                                   jsonEntity.toObject().value("Name").toString(),
                                   _GetActionsFromJsonArray(jsonEntity.toObject().value("Actions").toArray())});
        }

        return entities;
    }

    QVector<EntityAction> FactionsManager::_GetActionsFromJsonArray(const QJsonArray& array)
    {
        QVector<EntityAction> actions;

        for (const auto & jsonAction : array)
        {
            const QString hotkeyString = jsonAction.toObject().value("HotkeyString").toString();

            actions.append(EntityAction{CSFPARSER->GetClearName(hotkeyString),
                                        jsonAction.toObject().value("IconName").toString(),
                                        QChar{static_cast<char16_t>(CSFPARSER->GetHotkey(hotkeyString))}});
        }

        return actions;
    }
#pragma endregion
