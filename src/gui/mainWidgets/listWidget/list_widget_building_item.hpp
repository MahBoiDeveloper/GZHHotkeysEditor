#pragma once

#include <QListWidgetItem>
#include "../../../data/building.h"

class ListWidgetBuildingItem : public QListWidgetItem
{
public:
    explicit ListWidgetBuildingItem(const Building& building);

private:
    Building building;
};
