#include <QJsonArray>
#include <QJsonObject>

#include "FactionsManager.hpp"
#include "../Parsers/JSONFile.hpp"
#include "../Parsers/CSFParser.hpp"


FactionsManager::FactionsManager(const QString& techTreeFilePath, QObject *parent)
    : QObject{parent}
    , pTechTree{new JSONFile{techTreeFilePath}}
    , ActionsPool{}
    , EntitiesPool{}
    , Factions{_GetTechTreeFactions()}
{}

const QVector<Faction>& FactionsManager::GetFactions() const
{
    return Factions;
}

const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> FactionsManager::GetFactionEntities(const QString& factionShortName) const
{
    const Faction* const faction = _GetFactionByShortName(factionShortName);

    if (faction == nullptr) return {};

    return faction->GetEntitiesMap();
}

const QVector<QSharedPointer<EntityAction>> FactionsManager::GetEntityActions(const QString& factionShortName, const QString& entityName) const
{
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> factionEntities = GetFactionEntities(factionShortName);

    for (const auto & currentEntitiesType : factionEntities)
    {
        for (const auto & entity : currentEntitiesType)
        {
            if (entity->GetName() == entityName)
            {
                return entity->GetActions();
            }
        }
    }

    return {};
}

void FactionsManager::SetEntityActionHotkey(const QString& factionShortName,
                                            const QString& entityName,
                                            const QString& actionName,
                                            const QString& hotkey)
{
     QVector<QSharedPointer<EntityAction>> entityActions = GetEntityActions(factionShortName, entityName);

    for (auto & entityAction : entityActions)
    {
        // Skip if wrong action
        if (entityAction->getName() != actionName) continue;

        entityAction->setHotkey(hotkey);
    }
}

const Faction* FactionsManager::_GetFactionByShortName(const QString& factionShortName) const
{
    for (const auto & faction : Factions)
    {
        if (faction.GetShortName() == factionShortName)
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
                QVector<QSharedPointer<const Entity>> entities = _GetEntitiesFromJsonArray(factionObject.value(it.value()).toArray());
                if (!entities.isEmpty())
                {
                    newFaction.AddEntities(it.key(), entities);
                }
            }

            factions.append(newFaction);
        }

        return factions;
    }

    QVector<QSharedPointer<const Entity>> FactionsManager::_GetTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName)
    {
        for (const auto& jsonFaction : pTechTree->Query("$.TechTree").toArray())
        {
            if (factionShortName == jsonFaction.toObject().value("ShortName").toString())
            {
                return _GetEntitiesFromJsonArray(jsonFaction.toObject().value(Config::ENTITIES_STRINGS.value(entity)).toArray());
            }
        }

        return {};
    }

    QVector<QSharedPointer<const Entity>> FactionsManager::_GetEntitiesFromJsonArray(const QJsonArray& array)
    {
        QVector<QSharedPointer<const Entity>> entities;

        for (const auto & jsonEntity : array)
        {
            const QString hotkeyString = jsonEntity.toObject().value("IngameName").toString();

            if (!EntitiesPool.contains(hotkeyString))
            {
                EntitiesPool.insert(hotkeyString, QSharedPointer<const Entity>::create(CSFPARSER->GetStringValue(hotkeyString),
                                                                                       jsonEntity.toObject().value("Name").toString(),
                                                                                       _GetActionsFromJsonArray(jsonEntity.toObject().value("Actions").toArray())));
            }

            entities.append(EntitiesPool.value(hotkeyString));
        }

        return entities;
    }

    QVector<QSharedPointer<EntityAction>> FactionsManager::_GetActionsFromJsonArray(const QJsonArray& array)
    {
        QVector<QSharedPointer<EntityAction>> actions;

        for (const auto & jsonAction : array)
        {
            const QString hotkeyString = jsonAction.toObject().value("HotkeyString").toString();

            if (!ActionsPool.contains(hotkeyString))
            {
                ActionsPool.insert(hotkeyString, QSharedPointer<EntityAction>::create(CSFPARSER->GetClearName(hotkeyString),
                                                                                      jsonAction.toObject().value("IconName").toString(),
                                                                                      QChar{static_cast<char16_t>(CSFPARSER->GetHotkey(hotkeyString))}));
            }

            actions.append(ActionsPool.value(hotkeyString));
        }

        return actions;
    }
#pragma endregion
