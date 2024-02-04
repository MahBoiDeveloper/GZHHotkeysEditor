#pragma once
#include <QSet>
#include <QVector>
#include <QSharedPointer>
#include "EntityAction.hpp"

class Entity
{
public:
    Entity(const QString& name, const QString& iconName, const QVector<QVector<QSharedPointer<EntityAction>>>& actionPanels);
    const QString& getName() const;
    const QString& getIconName() const;
    const QVector<QVector<QSharedPointer<EntityAction>>>& getActionPanels() const;
    int getPanelsCount() const;

private:
    QString name;
    QString iconName;
    QVector<QVector<QSharedPointer<EntityAction>>> actionPanels;
};
