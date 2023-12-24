#pragma once

#include <QListWidgetItem>
#include <building.hpp>

class ListWidgetBuildingItem : public QListWidgetItem
{
public:
    explicit ListWidgetBuildingItem(const Building& building);

private:
    Building building;
};
