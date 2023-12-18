#include "list_widget_building_item.hpp"
#include "../config.hpp"

ListWidgetBuildingItem::ListWidgetBuildingItem(const Building& building)
    : QListWidgetItem{}
    , building{building}
{
    setIcon(QPixmap::fromImage(Config::decodeWebpIcon(QString::fromStdString(building.getIconName()))));
}
