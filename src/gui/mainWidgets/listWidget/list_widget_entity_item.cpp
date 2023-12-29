#include "list_widget_entity_item.hpp"
#include <gui_config.hpp>

ListWidgetEntityItem::ListWidgetEntityItem(const QString& name)
    : QListWidgetItem{}
{
    setText(name);
    setIcon(QPixmap::fromImage(GuiConfig::decodeWebpIcon(name)));
}
