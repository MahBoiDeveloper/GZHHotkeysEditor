#include "list_widget_building_item.hpp"
#include <gui_config.hpp>

ListWidgetBuildingItem::ListWidgetBuildingItem(const Building& building)
    : QListWidgetItem{}
    , building{building}
{
    setIcon(QPixmap::fromImage(GuiConfig::decodeWebpIcon(QString::fromStdString(building.getIconName()))));
}
