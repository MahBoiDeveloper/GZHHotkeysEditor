#pragma once

#include <QButtonGroup>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <config.hpp>

#include <QScrollArea>
#include <faction.hpp>

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private slots:
    void onAbout();

private:
    void configureMenu();
    void setBuildingsList(const QString& factionShortName);
    void setHotkeysLayout(const QString& factionShortName);

private:
    QVector<Faction> factions;

    QButtonGroup factionsButtonsGroup;

//    QTreeWidget entitiesTreeWidget;
    QListWidget entitiesTreeWidget;

    QScrollArea hotkeysArea;
    std::unique_ptr<QWidget> hotkeysScrollWidgetPtr;

    std::unique_ptr<QDialog> aboutDialogPtr;
};
