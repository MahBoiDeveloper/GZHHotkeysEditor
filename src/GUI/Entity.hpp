#pragma once
#include <QSet>
#include <QVector>
#include <QSharedPointer>
#include "EntityAction.hpp"

class Entity
{
private: // Data
    QString name;
    QString iconName;
    QVector<QVector<QSharedPointer<EntityAction>>> actionPanels;

public: // Methods
    Entity(const QString& name, const QString& iconName, const QVector<QVector<QSharedPointer<EntityAction>>>& actionPanels);
    int            GetPanelsCount() const;
    const QString& GetName()        const;
    const QString& GetIconName()    const;
    const QVector<QVector<QSharedPointer<EntityAction>>>& GetActionPanels() const;
    
};
