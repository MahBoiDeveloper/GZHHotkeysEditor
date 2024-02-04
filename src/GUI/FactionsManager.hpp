#pragma once
#include <QObject>
#include <QSet>
#include "Faction.hpp"

class JSONFile;

class FactionsManager : public QObject
{
    Q_OBJECT

private: // Data
    QMap<QSharedPointer<const Entity>, QVector<QSet<QString>>> entitiesPanelsCollisionKeys;
    QMap<QString, QSharedPointer<EntityAction>> actionsPool;
    QMap<QString, QSharedPointer<const Entity>> entitiesPool;
    const QSharedPointer<const JSONFile> pTechTree;
    const QVector<Faction> FACTIONS;

private: // Methods
    const Faction* _GetFactionByShortName(const QString& factionShortName) const;
    void           _AppendNewCollisionsForHotkey(const QString& newHotkey);
    void           _UpdateHotkeyCollisions(const QString& oldHotkey, const QString& newHotkey);

    QVector<Faction>                      _GetTechTreeFactions();
    QVector<QSharedPointer<const Entity>> _GetTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName);
    QVector<QSharedPointer<const Entity>> _GetEntitiesFromJsonArray(const QJsonArray& array);
    QVector<QSharedPointer<EntityAction>> _GetActionsFromJsonArray(const QJsonArray& array);

public:
    explicit FactionsManager(const QString& techTreeFilePath, QObject* parent = nullptr);
    
    const QVector<Faction>&                                                  GetFactions()                                                                     const;
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> GetFactionEntities(const QString& factionShortName)                               const;
    const QVector<QVector<QSharedPointer<EntityAction>>>                     GetEntityActionPanels(const QString& factionShortName, const QString& entityName) const;
    const QVector<QSet<QString>>                                             GetEntityCollisionsKeys(const QSharedPointer<const Entity>& entity)               const;
    const QVector<QSet<QString>>                                             GetEntityCollisionsKeys(const QString& entityName)                                const;
    void SetEntityActionHotkey(const QString& factionShortName,
                               const QString& entityName,
                               const QString& actionName,
                               const QString& hotkey);
};
