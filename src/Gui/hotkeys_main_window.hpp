#pragma once

#include <QButtonGroup>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QTreeWidgetItem>

#include <QScrollArea>
#include "../Data/faction.hpp"

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private slots:
    void onAbout();

private:
    void configureMenu();
    void setEntitiesList(const QString& factionShortName);
    void setHotkeysLayout(const QString& factionShortName);

private:
    QVector<Faction> factions;
    QButtonGroup factionsButtonsGroup;

    // Graphic widgets in a single copy
    QTreeWidget* entitiesTreeWidget = nullptr;
    QScrollArea* hotkeysArea = nullptr;

    // Renewable widgets
    QWidget* hotkeysScrollWidget = nullptr;
    QDialog* aboutDialog = nullptr;
};
