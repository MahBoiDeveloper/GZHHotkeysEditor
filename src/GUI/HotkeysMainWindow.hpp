#pragma once

#include "FactionsManager.hpp"

#include <QMainWindow>

class QScrollArea;
class QTreeWidget;
class QButtonGroup;

class ActionHotkeyWidget;

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private:
    void configureMenu();
    void setEntitiesList(const QString& factionShortName);
    void setHotkeysPanelsWidget();
    void highlightKeys(const QString& entityName) const;

private slots:
    void onAbout();

private:
    FactionsManager factionsManager;

    // Qt object in a single copy
    QButtonGroup* pFactionsButtonsGroup = nullptr;

    // Graphic widgets in a single copy
    QTreeWidget* pEntitiesTreeWidget    = nullptr;
    QScrollArea* pHotkeysArea           = nullptr;

    // Renewable widgets
    QTabWidget* pHotkeysPanelsWidget    = nullptr;
    QDialog* pAboutDialog               = nullptr;

    QVector<QSet<ActionHotkeyWidget*>> hotkeyWdgets;
};
