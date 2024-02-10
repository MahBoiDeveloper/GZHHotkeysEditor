#pragma once
#include <QMap>
#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include "../Config.hpp"

class Faction
{
public: // Types
    struct Action
    {
        QString iconName;
        QString hotkeyString;
    };

    struct GameObject
    {
        QString iconName;
        QString ingameName;
        QVector<QVector<Action>> keyboardLayouts;
    };

private: // Data
    QString shortName;
    QString displayName;
    QString displayNameDescription;
    QMap<Config::GameObjectTypes, GameObject> techTree;
public:
    inline static const int BASIC_FACTION_COUNT = 12;

private: // Methods
    QMap<Config::GameObjectTypes, GameObject> ParseJsonObject(const QJsonObject& obj);
public:
    Faction();
    Faction(const QString& _shortName, const QString& _displayName, const QString& _displayNameDescription);
    Faction(const QJsonObject& factionAsObject);

    const QString& GetShortName() const;
    const QString& GetDisplayName() const;
    const QString& GetDisplayNameDescription() const;
    const QMap<Config::GameObjectTypes, GameObject>& GetTechTree() const;

    const QVector<QVector<Action>>& GetKeyboardLayoutsByObjectName(const QString& objName) const;

    void SetHotkey(const QString& goName, const QString& actName, const QString& hk);
};
