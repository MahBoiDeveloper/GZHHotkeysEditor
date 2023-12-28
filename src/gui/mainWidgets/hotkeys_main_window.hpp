#pragma once

#include <QButtonGroup>
#include <QListWidget>
#include <QMainWindow>

class HotkeysMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HotkeysMainWindow(const QVariant& configuration, QWidget* parent = nullptr);

private:
    void _configureMenu();
    QLayout* _createFactionsButtonsLayout() const;
    QListWidget* _createBuildingsList(const QString& factionName) const;
    QLayout* _createHotkeysLayout() const;
    QLayout* _createTabContent(const QString& factionName) const;

private slots:
    void setCurrentTab(int negativeId);
    void onAbout();

private:
    QButtonGroup* factionsButtonsGroup;
    QTabWidget* factionsTabs;
    QDialog* aboutDialog = nullptr;
};
