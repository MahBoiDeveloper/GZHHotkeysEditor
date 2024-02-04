#pragma once
#include <QMainWindow>
#include "FactionsManager.hpp"

class QScrollArea;
class QTreeWidget;
class QButtonGroup;

class ActionHotkeyWidget;

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

private: // Data
    FactionsManager factionsManager;

    // Qt object in a single copy
    QButtonGroup* pFactionsButtonsGroup = nullptr;

    // Graphic widgets in a single copy
    QTreeWidget*  pEntitiesTreeWidget   = nullptr;
    QScrollArea*  pHotkeysArea          = nullptr;

    // Renewable widgets
    QTabWidget*   pHotkeysPanelsWidget  = nullptr;
    QDialog*      pAboutDialog          = nullptr;

    QVector<QSet<ActionHotkeyWidget*>> hotkeyWdgets;

public: // Methods
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private:
    /// @brief Set context menu bar functions and logics.
    void ConfigureMenu();
    void SetEntitiesList(const QString& factionShortName);
    void SetHotkeysPanelsWidget();
    /// @brief Set hotkeys colors. Default color is black. Changes color to red for keys, that is conflict to each other in one unit/building.
    void HighlightKeys(const QString& entityName) const;

private slots:
    void OnAbout();
};
