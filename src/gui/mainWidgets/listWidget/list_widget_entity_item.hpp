#pragma once

#include <QListWidgetItem>
#include <entity_action.hpp>

class ListWidgetEntityItem : public QListWidgetItem
{
public:
    explicit ListWidgetEntityItem(const QString& name);
};
