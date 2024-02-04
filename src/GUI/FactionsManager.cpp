#include <QJsonArray>
#include <QJsonObject>
#include <QKeySequence>

#include "../Parsers/JSONFile.hpp"
#include "../Parsers/CSFParser.hpp"

#include "FactionsManager.hpp"

FactionsManager::FactionsManager(const QString& techTreeFilePath, QObject *parent)
    : QObject{parent}
    , pTechTree{new JSONFile{techTreeFilePath}}
    , factions{_getTechTreeFactions()}
{
    // Update collisions sets for all available keys
    for (Qt::Key key = Config::AVAILABLE_KEYS.first; key <= Config::AVAILABLE_KEYS.second; key = static_cast<Qt::Key>(key+1))
    {
        _appendNewCollisionsForHotkey(QKeySequence(key).toString());
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

const QVector<Faction>& FactionsManager::getFactions() const
{
    return factions;
}

const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> FactionsManager::getFactionEntities(const QString& factionShortName) const
{
    const Faction* const faction = _getFactionByShortName(factionShortName);

    if (faction == nullptr) return {};

    return faction->GetEntitiesMap();
}

const QVector<QVector<QSharedPointer<EntityAction>>> FactionsManager::getEntityActionPanels(const QString& factionShortName, const QString& entityName) const
{
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> factionEntities = getFactionEntities(factionShortName);

    for (const auto & currentEntitiesType : factionEntities)
    {
        for (const auto & entity : currentEntitiesType)
        {
            if (entity->getName() == entityName)
            {
                return entity->getActionPanels();
            }
        }
    }

    return {};
}

void FactionsManager::setEntityActionHotkey(const QString& factionShortName,
                                            const QString& entityName,
                                            const QString& actionName,
                                            const QString& hotkey)
{
    const QVector<QVector<QSharedPointer<EntityAction>>> entityActionPanels = getEntityActionPanels(factionShortName, entityName);

    for (const auto & actionPanel : entityActionPanels)
    {
        for (auto & entityAction : actionPanel)
        {
            // Skip wrong action
            if (entityAction->getName() != actionName) continue;

            // Set hotkey
            const QString oldHotkey = entityAction->getHotkey();
            entityAction->setHotkey(hotkey);

            // Update new collisions and quit
            _updateHotkeyCollisions(oldHotkey, hotkey);
            return;
        }
    }
}

const QVector<QSet<QString>> FactionsManager::getEntityCollisionsKeys(const QSharedPointer<const Entity>& entity) const
{
    return entitiesPanelsCollisionKeys.value(entity);
}

const QVector<QSet<QString>> FactionsManager::getEntityCollisionsKeys(const QString& entityName) const
{
    for (const auto & entity : entitiesPool)
    {
        if (entity->getName() == entityName)
        {
            return getEntityCollisionsKeys(entity);
        }
    }

    return {};
}

const Faction* FactionsManager::_getFactionByShortName(const QString& factionShortName) const
{
    for (const auto & faction : factions)
    {
        // Find the right faction
        if (faction.GetShortName() == factionShortName)
        {
            return &faction;
        }
    }
    return nullptr;
}

void FactionsManager::_appendNewCollisionsForHotkey(const QString& newHotkey)
{
    for (const auto & faction : factions)
    {
        for (const auto & entity : faction.GetAllEntities())
        {
            QVector<QSet<QString>> newPanelsCollisionSets = entitiesPanelsCollisionKeys.value(entity);

            const QVector<QVector<QSharedPointer<EntityAction>>>& entityPanels = entity->getActionPanels();

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
                    if (action->getHotkey() == newHotkey) ++hotkeyActionsCount;
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

void FactionsManager::_updateHotkeyCollisions(const QString& oldHotkey, const QString& newHotkey)
{
    QSet<QSharedPointer<const Entity>> noCollisionEntities;

    // For all entities in collision set
    for (auto it = entitiesPanelsCollisionKeys.constBegin(); it != entitiesPanelsCollisionKeys.constEnd(); ++it)
    {
        QVector<QSet<QString>> newEntityCollisionPanels = it.value();

        // Panel index
        int i = -1;

        // For all entity panels
        for (const auto & panel : it.key()->getActionPanels())
        {
            // Increase index
            ++i;

            int hotkeyActionsCount = 0;

            for (const auto & action : panel)
            {
                if (action->getHotkey() == oldHotkey) ++hotkeyActionsCount;
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
    _appendNewCollisionsForHotkey(newHotkey);


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
    QVector<Faction> FactionsManager::_getTechTreeFactions()
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
                QVector<QSharedPointer<const Entity>> entities = _getEntitiesFromJsonArray(factionObject.value(it.value()).toArray());
                if (!entities.isEmpty())
                {
                    newFaction.AddEntities(it.key(), entities);
                }
            }

            factions.append(newFaction);
        }

        return factions;
    }

    QVector<QSharedPointer<const Entity>> FactionsManager::_getTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName)
    {
        for (const auto& jsonFaction : pTechTree->Query("$.TechTree").toArray())
        {
            if (factionShortName == jsonFaction.toObject().value("ShortName").toString())
            {
                return _getEntitiesFromJsonArray(jsonFaction.toObject().value(Config::ENTITIES_STRINGS.value(entity)).toArray());
            }
        }

        return {};
    }

    QVector<QSharedPointer<const Entity>> FactionsManager::_getEntitiesFromJsonArray(const QJsonArray& array)
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
                    actionPanels.append(_getActionsFromJsonArray(jsonPanel.toArray()));
                }

                entitiesPool.insert(name, QSharedPointer<const Entity>::create(CSFPARSER->GetStringValue(hotkeyString), name, actionPanels));
            }

            entities.append(entitiesPool.value(name));
        }

        return entities;
    }

    QVector<QSharedPointer<EntityAction>> FactionsManager::_getActionsFromJsonArray(const QJsonArray& array)
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
