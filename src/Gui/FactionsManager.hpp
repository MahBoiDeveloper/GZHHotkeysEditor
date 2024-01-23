#pragma once

#include <QObject>

#include "../Data/Faction.hpp"

class JSONFile;

class FactionsManager : public QObject
{
    Q_OBJECT

public:
    explicit FactionsManager(const QString& techTreeFilePath, QObject* parent = nullptr);
    const QVector<Faction>& GetFactions() const;
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> GetFactionEntities(const QString& factionShortName) const;
    const QVector<QSharedPointer<EntityAction> > GetEntityActions(const QString& factionShortName, const QString& entityName) const;
    void SetEntityActionHotkey(const QString& factionShortName,
                               const QString& entityName,
                               const QString& actionName,
                               const QString& hotkey);

private:
    const Faction* _GetFactionByShortName(const QString& factionShortName) const;

private:
    QVector<Faction>      _GetTechTreeFactions();
    QVector<QSharedPointer<const Entity>> _GetTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName);
    QVector<QSharedPointer<const Entity>> _GetEntitiesFromJsonArray(const QJsonArray& array);
    QVector<QSharedPointer<EntityAction>> _GetActionsFromJsonArray(const QJsonArray& array);

private:
    const QSharedPointer<const JSONFile> pTechTree;
    QMap<QString, QSharedPointer<EntityAction>> ActionsPool;
    QMap<QString, QSharedPointer<const Entity>> EntitiesPool;
    QVector<Faction> Factions;
};
