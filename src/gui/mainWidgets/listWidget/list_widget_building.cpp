#include "list_widget_building.hpp"

ListWidgetBuilding::ListWidgetBuilding(QWidget* parent)
    : QListWidget{parent}
    , iconBaseSize{40, 40}
{

}

void ListWidgetBuilding::resizeEvent(QResizeEvent *event)
{
//  настройка размера изобрадения элемента списка
    double newSpacing = height() * 0.02;
    setSpacing(newSpacing); //промежуток в 2% от высоты
    int delta = 2 * (newSpacing + contentsMargins().top());
    int iconHeight = (height() - delta); //размер иконки
    //немного уменьшить коэффициент
    double k = (double)iconBaseSize.width() / iconBaseSize.height() * 0.95;
    //задать размер иконки
    setIconSize(QSize(iconHeight * k, iconHeight));

    QListWidget::resizeEvent(event);
}
