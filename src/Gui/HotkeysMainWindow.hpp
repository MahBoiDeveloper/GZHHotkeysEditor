#pragma once

#include <QMainWindow>

#include "FactionsManager.hpp"

class QScrollArea;
class QTreeWidget;
class QButtonGroup;

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private:
    FactionsManager FactionsManager;

    // Qt object in a single copy
    QButtonGroup* pFactionsButtonsGroup = nullptr;

    // Graphic widgets in a single copy
    QTreeWidget* pEntitiesTreeWidget    = nullptr;
    QScrollArea* pHotkeysArea           = nullptr;

    // Renewable widgets
    QWidget* pHotkeysScrollWidget       = nullptr;
    QDialog* pAboutDialog               = nullptr;

private:
    void ConfigureMenu();
    void SetEntitiesList(const QString& factionShortName);
    void SetHotkeysLayout();

private slots:
    void OnAbout();
};
