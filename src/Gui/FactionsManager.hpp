#pragma once

#include <QObject>
#include <QSharedPointer>

#include "../Data/Faction.hpp"

class JSONFile;

class FactionsManager : public QObject
{
    Q_OBJECT

public:
    explicit FactionsManager(const QString& techTreeFilePath, QObject* parent = nullptr);
    const QVector<Faction>& GetFactions() const;
    const QMap<Config::EntitiesTypes, QVector<Entity>>* GetFactionEntities(const QString& factionShortName) const;
    const QVector<EntityAction>* GetEntityActions(const QString& factionShortName, const QString& entityName) const;
    void SetEntityActionHotkey(const QString& factionShortName,
                               const QString& entityName,
                               const QString& actionName,
                               const QString& hotkey);

private:
    const Faction* _GetFactionByShortName(const QString& factionShortName) const;

private:
    QVector<Faction>      _GetTechTreeFactions();
    QVector<Entity>       _GetTechTreeFactionEntities(Config::EntitiesTypes entity, const QString& factionShortName);
    QVector<Entity>       _GetEntitiesFromJsonArray(const QJsonArray& array);
    QVector<EntityAction> _GetActionsFromJsonArray(const QJsonArray& array);

private:
    const QSharedPointer<const JSONFile> pTechTree;
    QVector<Faction> Factions;
};
