#pragma once

#include "../Data/Faction.hpp"

#include <QObject>
#include <QSet>

class JSONFile;

class FactionsManager : public QObject
{
    Q_OBJECT

public:
    explicit FactionsManager(const QString& techTreeFilePath, QObject* parent = nullptr);
    const QVector<Faction>& getFactions() const;
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> getFactionEntities(const QString& factionShortName) const;
    const QVector<QVector<QSharedPointer<EntityAction>>> getEntityActionPanels(const QString& factionShortName, const QString& entityName) const;
    const QVector<QSet<QString>> getEntityCollisionsKeys(const QSharedPointer<const Entity>& entity) const;
    const QVector<QSet<QString>> getEntityCollisionsKeys(const QString& entityName) const;
    void setEntityActionHotkey(const QString& factionShortName,
                               const QString& entityName,
                               const QString& actionName,
                               const QString& hotkey);

private:
    const Faction* _getFactionByShortName(const QString& factionShortName) const;
    void _appendNewCollisionsForHotkey(const QString& newHotkey);
    void _updateHotkeyCollisions(const QString& oldHotkey, const QString& newHotkey);

private:
    QVector<Faction> _getTechTreeFactions();
    QVector<QSharedPointer<const Entity>> _getTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName);
    QVector<QSharedPointer<const Entity>> _getEntitiesFromJsonArray(const QJsonArray& array);
    QVector<QSharedPointer<EntityAction> > _getActionsFromJsonArray(const QJsonArray& array);

private:
    QMap<QSharedPointer<const Entity>, QVector<QSet<QString>>> entitiesPanelsCollisionKeys;
    QMap<QString, QSharedPointer<EntityAction>> actionsPool;
    QMap<QString, QSharedPointer<const Entity>> entitiesPool;
    const QSharedPointer<const JSONFile> pTechTree;
    const QVector<Faction> factions;
};
