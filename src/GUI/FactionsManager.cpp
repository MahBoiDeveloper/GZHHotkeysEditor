#include <QJsonArray>
#include <QJsonObject>
#include <QKeySequence>

#include "../Parsers/JSONFile.hpp"
#include "../Parsers/CSFParser.hpp"

#include "FactionsManager.hpp"

FactionsManager::FactionsManager(const QString& techTreeFilePath, QObject* parent)
    : QObject{parent}
    , pTechTree{new JSONFile{techTreeFilePath}}
    , FACTIONS{_GetTechTreeFactions()}
{
    // Update collisions sets for all available keys
    for (Qt::Key key = Config::AVAILABLE_KEYS.first; key <= Config::AVAILABLE_KEYS.second; key = static_cast<Qt::Key>(key+1))
    {
        _AppendNewCollisionsForHotkey(QKeySequence(key).toString());
    }

    // TODO: temporary
    //    if (entitiesPanelsCollisionKeys.isEmpty())
    //    {
    //        qDebug() << "\n" << "No collisions" << "\n";
    //        return;
    //    }
    //    qDebug() << "\n" << "======== Collisions ========";
    //    for (auto it = entitiesPanelsCollisionKeys.cbegin(); it != entitiesPanelsCollisionKeys.cend(); ++it)
    //    {
    //        qDebug() << "\n" << "Entity name:" << it.key()->getName();
    //        for (const auto & key : it.value())
    //        {
    //            qDebug() << " - " << key;
    //        }
    //    }
    //    qDebug() << "\n";
}

const QVector<Faction>& FactionsManager::GetFactions() const
{
    return FACTIONS;
}

const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> FactionsManager::GetFactionEntities(const QString& factionShortName) const
{
    const Faction* const faction = _GetFactionByShortName(factionShortName);

    if (faction == nullptr) return {};

    return faction->GetEntitiesMap();
}

const QVector<QVector<QSharedPointer<EntityAction>>> FactionsManager::GetEntityActionPanels(const QString& factionShortName, const QString& entityName) const
{
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> factionEntities = GetFactionEntities(factionShortName);

    for (const auto & currentEntitiesType : factionEntities)
    {
        for (const auto & entity : currentEntitiesType)
        {
            if (entity->GetName() == entityName)
            {
                return entity->GetActionPanels();
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
    const QVector<QVector<QSharedPointer<EntityAction>>> entityActionPanels = GetEntityActionPanels(factionShortName, entityName);

    for (const auto & actionPanel : entityActionPanels)
    {
        for (auto & entityAction : actionPanel)
        {
            // Skip wrong action
            if (entityAction->GetName() != actionName) continue;

            // Set hotkey
            const QString oldHotkey = entityAction->GetHotkey();
            entityAction->SetHotkey(hotkey);

            // Update new collisions and quit
            _UpdateHotkeyCollisions(oldHotkey, hotkey);
            return;
        }
    }
}

const QVector<QSet<QString>> FactionsManager::GetEntityCollisionsKeys(const QSharedPointer<const Entity>& entity) const
{
    return entitiesPanelsCollisionKeys.value(entity);
}

const QVector<QSet<QString>> FactionsManager::GetEntityCollisionsKeys(const QString& entityName) const
{
    for (const auto & entity : entitiesPool)
    {
        if (entity->GetName() == entityName)
        {
            return GetEntityCollisionsKeys(entity);
        }
    }

    return {};
}

const Faction* FactionsManager::_GetFactionByShortName(const QString& factionShortName) const
{
    for (const auto & faction : FACTIONS)
    {
        // Find the right faction
        if (faction.GetShortName() == factionShortName)
        {
            return &faction;
        }
    }
    return nullptr;
}

void FactionsManager::_AppendNewCollisionsForHotkey(const QString& newHotkey)
{
    for (const auto & faction : FACTIONS)
    {
        for (const auto & entity : faction.GetAllEntities())
        {
            QVector<QSet<QString>> newPanelsCollisionSets = entitiesPanelsCollisionKeys.value(entity);

            const QVector<QVector<QSharedPointer<EntityAction>>>& entityPanels = entity->GetActionPanels();

            // Panel index
            int i = -1;

            // for all entity panels
            for (const auto & panel : entityPanels)
            {
                // Increase panel index
                ++i;

                if (newPanelsCollisionSets.size() < i + 1)
                {
                    // Align the collisions vector by the number of panels
                    newPanelsCollisionSets.append(QSet<QString>{});
                }
                else if (newPanelsCollisionSets.at(i).contains(newHotkey))
                {
                    // Skip the key already in collision set for current panel
                    continue;
                }

                int hotkeyActionsCount = 0;

                for (const auto & action : panel)
                {
                    if (action->GetHotkey() == newHotkey) ++hotkeyActionsCount;
                }

                // If there ARE collisions for a new hotkey in current panel -> insert the key into the set
                if (hotkeyActionsCount > 1)
                {
                    newPanelsCollisionSets[i].insert(newHotkey);
                }
            }

            bool isCollisionsEmpty = true;
            for (const auto & collsionSet : newPanelsCollisionSets)
            {
                // If collision found -> stop searching
                if (!collsionSet.isEmpty())
                {
                    isCollisionsEmpty = false;
                    break;
                }
            }

            // Skip if no collisions with the entity
            if (isCollisionsEmpty) continue;

            // Save collisions for the entity
            entitiesPanelsCollisionKeys.insert(entity, newPanelsCollisionSets);
        }
    }
}

void FactionsManager::_UpdateHotkeyCollisions(const QString& oldHotkey, const QString& newHotkey)
{
    QSet<QSharedPointer<const Entity>> noCollisionEntities;

    // For all entities in collision set
    for (auto it = entitiesPanelsCollisionKeys.constBegin(); it != entitiesPanelsCollisionKeys.constEnd(); ++it)
    {
        QVector<QSet<QString>> newEntityCollisionPanels = it.value();

        // Panel index
        int i = -1;

        // For all entity panels
        for (const auto & panel : it.key()->GetActionPanels())
        {
            // Increase index
            ++i;

            int hotkeyActionsCount = 0;

            for (const auto & action : panel)
            {
                if (action->GetHotkey() == oldHotkey) ++hotkeyActionsCount;
            }

            // If there are NO collision -> remove key from current panel
            if (hotkeyActionsCount <= 1)
            {
                newEntityCollisionPanels[i].remove(oldHotkey);
            }

        }

        // Check that the entity still has collisions
        bool emptyCollisions = true;
        for (const auto & set : newEntityCollisionPanels)
        {
            if (!set.isEmpty())
            {
                emptyCollisions = false;
                break;
            }
        }

        // If there are NO collisions for current entity -> prepare it to be removed from collisons
        if (emptyCollisions)
        {
            noCollisionEntities.insert(it.key());
        }
        else
        {
            // Insert new collisions panels for current entity
            entitiesPanelsCollisionKeys.insert(it.key(), newEntityCollisionPanels);
        }
    }

    // Remove no collisions entities
    for (const auto & entity : noCollisionEntities)
    {
        entitiesPanelsCollisionKeys.remove(entity);
    }

    // Append new hotkey collisions
    _AppendNewCollisionsForHotkey(newHotkey);

    // TODO: temporary
    //    if (entitiesPanelsCollisionKeys.isEmpty())
    //    {
    //        qDebug() << "\n" << "No collisions" << "\n";
    //        return;
    //    }
    //    qDebug() << "\n" << "======== Collisions ========";
    //    for (auto it = entitiesPanelsCollisionKeys.cbegin(); it != entitiesPanelsCollisionKeys.cend(); ++it)
    //    {
    //        qDebug() << "\n" << "Entity name:" << it.key()->getName();
    //        for (const auto & key : it.value())
    //        {
    //            qDebug() << " - " << key;
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

            if (!entitiesPool.contains(name))
            {
                QVector<QVector<QSharedPointer<EntityAction>>> actionPanels;

                for (const auto & jsonPanel : jsonEntity.toObject().value("KeyboardLayouts").toArray())
                {
                    actionPanels.append(_GetActionsFromJsonArray(jsonPanel.toArray()));
                }

                entitiesPool.insert(name, QSharedPointer<const Entity>::create(CSFPARSER->GetStringValue(hotkeyString), name, actionPanels));
            }

            entities.append(entitiesPool.value(name));
        }

        return entities;
    }

    QVector<QSharedPointer<EntityAction>> FactionsManager::_GetActionsFromJsonArray(const QJsonArray& array)
    {
        QVector<QSharedPointer<EntityAction>> actions;

        for (const auto & jsonAction : array)
        {
            const QString hotkeyString = jsonAction.toObject().value("HotkeyString").toString();

            if (!actionsPool.contains(hotkeyString))
            {
                actionsPool.insert(hotkeyString, QSharedPointer<EntityAction>::create(CSFPARSER->GetClearName(hotkeyString),
                                                                                      jsonAction.toObject().value("IconName").toString(),
                                                                                      QChar{static_cast<char16_t>(CSFPARSER->GetHotkey(hotkeyString))}));
            }

            actions.append(actionsPool.value(hotkeyString));
        }

        return actions;
    }
#pragma endregion
