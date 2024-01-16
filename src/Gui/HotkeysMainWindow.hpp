#pragma once
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QScrollArea>
#include "../Config.hpp"
#include "../Data/Faction.hpp"
#include "../Parsers/JSONFile.hpp"

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

public: // Data
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);
private:
    // Graphic widgets in a single copy
    QTreeWidget* pEntitiesTreeWidget = nullptr;
    QScrollArea* pHotkeysArea        = nullptr;

    QVector<Faction> factions;
    QButtonGroup     factionsButtonsGroup;

    // Renewable widgets
    QWidget* hotkeysScrollWidget = nullptr;
    QDialog* aboutDialog         = nullptr;

    JSONFile TechTree{Config::techTreeFile};

private: // Methods
    void                  ConfigureMenu();
    void                  SetEntitiesList(const QString& factionShortName);
    void                  SetHotkeysLayout();
    QVector<Faction>      GetFactions();
    QVector<Entity>       GetFactionEntities(Config::Entities entity, const QString& factionShortName);
    QVector<Entity>       GetEntitiesFromJsonArray(const QJsonArray& array);
    QVector<EntityAction> GetActionsFromJsonArray(const QJsonArray& array);
    QVector<EntityAction> GetEntityActions(const QString& entityName);
private slots:
    void onAbout();
};
