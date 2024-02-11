#pragma once
#include <QMainWindow>
#include "../Parsers/JSONFile.hpp"
#include "Faction.hpp"

class QScrollArea;
class QTreeWidget;
class QButtonGroup;

class ActionHotkeyWidget;

class HotkeysMainWindow final : public QMainWindow
{
    Q_OBJECT

private: // Data
    JSONFile TECH_TREE_SOURCE{Config::TECH_TREE_PATH};

    QVector<Faction> factionVector;

    // Qt object in a single copy
    QButtonGroup* pFactionsButtonsGroup = nullptr;

    // Graphic widgets in a single copy
    QTreeWidget*  pEntitiesTreeWidget   = nullptr;
    QScrollArea*  pHotkeysArea          = nullptr;

    // Renewable widgets
    QTabWidget*   pHotkeysPanelsWidget  = nullptr;
    QDialog*      pAboutDialog          = nullptr;

    QVector<QSet<ActionHotkeyWidget*>> vHotkeyWidgets;

public: // Methods
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private:
    /// @brief Read data from TechTree.json and parse it to game objects.
    void SetFactions();
    /// @brief Return faction from HotkeysMainWindow::factionVector vector.
    const Faction& GetFactionRef(const QString& name);
    /// @brief Set context menu bar functions and logics.
    void ConfigureMenu();
    /// @brief Set game object and their actions for window by short faction name.
    void SetGameObjectList(const QString& factionShortName);
    /// @brief Set game object to display.
    void SetHotkeysPanelsWidget();
    /// @brief Set hotkeys colors. Default color is black. Changes color to red for keys, that is conflict to each other in one unit/building.
    void HighlightKeys(const QString& fctIconName, const QString& goIconName) const;
    /// @brief Replace current action assigned hotkey with new one.
    void SetActionHotkey(const QString& fctShortName, const QString& goName, const QString& actName, const QString& hk);

private slots:
    void OnAbout();
};
