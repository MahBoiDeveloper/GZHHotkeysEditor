#pragma once
#include <QMainWindow>
#include <QScrollArea>
#include <QTreeWidgetItem>
#include <QButtonGroup>
#include <QHBoxLayout>

#include "../Parsers/JSONFile.hpp"
#include "../Faction.hpp"
#include "KeyboardLayout.hpp"
#include "ActionHotkeyWidget.hpp"

class EditorWindow final : public QMainWindow
{
    Q_OBJECT

private: // Data
    JSONFile TECH_TREE_SOURCE{PROGRAM_CONSTANTS->TECH_TREE_FILE};

    QVector<Faction> factionVector;

    // Qt object in a single copy
    QButtonGroup* pFactionsButtonsGroup = nullptr;

    // Graphic widgets in a single copy
    QTreeWidget*    pEntitiesTreeWidget = nullptr;
    QScrollArea*    pHotkeysArea        = nullptr;
    KeyboardLayout* pKeyboardLayout     = nullptr;

    // Renewable widgets
    QTabWidget*   pHotkeysPanelsWidget  = nullptr;
    QDialog*      pAboutDialog          = nullptr;
    QWidget*      pSettingsWindow       = nullptr;

    QVector<QSet<ActionHotkeyWidget*>> vHotkeyWidgets;

public: // Methods
    EditorWindow(QWidget* parent = nullptr);

private:
    /// @brief Read data from TechTree.json and parse it to game objects.
    void SetFactions();
    /// @brief Return faction from EditorWindow::factionVector vector.
    const Faction& GetFactionRef(const QString& name);
    /// @brief Set context menu bar functions and logics.
    void ConfigureMenu();
    /// @brief Set game object and their actions for window by short faction name.
    void SetGameObjectList(const QString& factionShortName);
    /// @brief Set game object to display.
    void SetHotkeysPanels();
    /// @brief Set hotkeys colors. Default color is black. Changes color to red for keys, that is conflict to each other in one unit/building.
    void HighlightCurrentKeys();
    /// @brief Replace current action assigned hotkey with new one.
    void SetActionHotkey(const QString& fctShortName, const QString& goName, const QString& actName, const QString& hk);
    /// @brief Creates line of keys for keyboard layout.
    QHBoxLayout* CreateKeysOnKeyboard(const QString& str);
    /// @brief Saves changes into file.
    void Save();

private slots:
    void ActAbout_Triggered();
    void ActSettings_Triggered();
    void ActSave_Triggered();
    void ActSaveAs_Triggered();
    void ActOpen_Triggered();

signals:
    Languages languageChanged(int index);
};
