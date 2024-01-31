#include <QJsonArray>
#include <QJsonObject>
#include <QKeySequence>

#include "FactionsManager.hpp"
#include "../Parsers/JSONFile.hpp"
#include "../Parsers/CSFParser.hpp"

FactionsManager::FactionsManager(const QString& techTreeFilePath, QObject *parent)
    : QObject{parent}
    , pTechTree{new JSONFile{techTreeFilePath}}
    , ActionsPool{}
    , EntitiesPool{}
    , Factions{_GetTechTreeFactions()}
{
    // Update collisions sets for all available keys
    for (Qt::Key key = Config::availableKeys.first; key <= Config::availableKeys.second; key = static_cast<Qt::Key>(key+1))
    {
        _UpdateCollisionsForHotkey(QKeySequence(key).toString());
    }

    // TODO: temporary
    //    if (HotkeyCollisions.isEmpty()) return;
    //    qDebug() << "\n" << "======== Collisions ========";
    //    for (auto it = HotkeyCollisions.cbegin(); it != HotkeyCollisions.cend(); ++it)
    //    {
    //        qDebug() << "\n" << "Key: " << it.key();
    //        for (const auto & entity : it.value())
    //        {
    //            qDebug() << " - entity name: " << entity->GetName();
    //        }
    //    }
    //    qDebug() << "\n";
}

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

        const QString oldHotkey = entityAction->getHotkey();
        entityAction->setHotkey(hotkey);
        _CheckHotkeyCollisions(oldHotkey, hotkey);
        return;
    }
}

const Faction* FactionsManager::_GetFactionByShortName(const QString& factionShortName) const
{
    for (const auto & faction : Factions)
    {
        // Find the right faction
        if (faction.GetShortName() == factionShortName)
        {
            return &faction;
        }
    }
    return nullptr;
}


void FactionsManager::_UpdateCollisionsForHotkey(const QString& newHotkey)
{
    QSet<QSharedPointer<const Entity>> newHotkeyCollisionsSet = HotkeyCollisions.value(newHotkey);

    for (const auto & faction : Factions)
    {
        for (const auto & entity : faction.GetAllEntities())
        {
            // Skip if entity already in collision set
            if (newHotkeyCollisionsSet.contains(entity)) continue;

            int hotkeyActionsCount = 0;

            for (const auto & action : entity->GetActions())
            {
                if (action->getHotkey() == newHotkey) ++hotkeyActionsCount;
            }

            // If there ARE collisions for a new hotkey in current entity -> insert it to the set
            if (hotkeyActionsCount > 1) newHotkeyCollisionsSet.insert(entity);
        }
    }

    // If the set are NOT empty -> add hotkey to collisions
    if (!newHotkeyCollisionsSet.isEmpty()) HotkeyCollisions.insert(newHotkey, newHotkeyCollisionsSet);
}

void FactionsManager::_CheckHotkeyCollisions(const QString& oldHotkey, const QString& newHotkey)
{
    if (HotkeyCollisions.contains(oldHotkey))
    {
        QSet<QSharedPointer<const Entity>> noCollisionEntities;

        // For all entities in collision set
        for (const auto & entity : HotkeyCollisions[oldHotkey])
        {
            int hotkeyActionsCount = 0;

            for (const auto & action : entity->GetActions())
            {
                if (action->getHotkey() == oldHotkey) ++hotkeyActionsCount;
            }

            // If there are NO collisions for an old hotkey in current entity -> prepare it to be removed from set
            if (hotkeyActionsCount <= 1) noCollisionEntities.insert(entity);
        }

        // Remove normal entities from collisions set
        HotkeyCollisions[oldHotkey].subtract(noCollisionEntities);

        // If the set has become empty -> delete old hotkey collisions section
        if (HotkeyCollisions[oldHotkey].isEmpty()) HotkeyCollisions.remove(oldHotkey);
    }

    _UpdateCollisionsForHotkey(newHotkey);

    // TODO: temporary
    //    if (HotkeyCollisions.isEmpty()) return;
    //    qDebug() << "\n" << "======== Collisions ========";
    //    for (auto it = HotkeyCollisions.cbegin(); it != HotkeyCollisions.cend(); ++it)
    //    {
    //        qDebug() << "\n" << "Key: " << it.key();
    //        for (const auto & entity : it.value())
    //        {
    //            qDebug() << " - entity name: " << entity->GetName();
    //        }
    //    }
    //    qDebug() << "\n";
}

#pragma region TechTree.json parsing methods
    QVector<Faction> FactionsManager::_GetTechTreeFactions()
    {
        QVector<Faction> factions;

        for (const auto& jsonFaction : pTechTree->Query("$.TechTree").toArray())
        {
            QJsonObject factionObject = jsonFaction.toObject();

            // TODO: check fields in file
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
            const QString name = jsonEntity.toObject().value("Name").toString();
            const QString hotkeyString = jsonEntity.toObject().value("IngameName").toString();

            if (!EntitiesPool.contains(name))
            {
                EntitiesPool.insert(name, QSharedPointer<const Entity>::create(CSFPARSER->GetStringValue(hotkeyString),
                                                                               name,
                                                                               _GetActionsFromJsonArray(jsonEntity.toObject().value("Actions").toArray())));
            }

            entities.append(EntitiesPool.value(name));
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
