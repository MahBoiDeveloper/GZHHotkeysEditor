#pragma once
#include <QPushButton>

// outdated resized widget (currently not in use)
class PushButton : public QPushButton
{
    Q_OBJECT
private:
    int baseHeight = 80;
    void setBaseHeight(int newParentWidgetHeight);
public:
    PushButton(const QString& text, QWidget* parent = nullptr);
    int getBaseHeight() const;
};
