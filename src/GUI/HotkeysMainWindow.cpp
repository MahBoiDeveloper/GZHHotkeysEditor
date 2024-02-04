#include <QMenuBar>
#include <QHeaderView>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QScrollArea>

#include "../Info.hpp"
#include "../Logger.hpp"

#include "ActionHotkeyWidget.hpp"
#include "GUIConfig.hpp"
#include "HotkeysMainWindow.hpp"

HotkeysMainWindow::HotkeysMainWindow(const QVariant& configuration, QWidget* parent)
    : QMainWindow(parent)
    , factionsManager{Config::TECH_TREE_PATH}
    , pFactionsButtonsGroup{new QButtonGroup{this}}
    , pEntitiesTreeWidget{new QTreeWidget}
    , pHotkeysArea{new QScrollArea}
    , pHotkeysPanelsWidget{nullptr}
    , pAboutDialog{nullptr}
{
    resize(1200, 800);
    ConfigureMenu();

    //============================ Entities Tree Widget configure =============================

    pEntitiesTreeWidget->header()->hide();
    // smooth scrolling
    pEntitiesTreeWidget->setVerticalScrollMode(QTreeWidget::ScrollMode::ScrollPerPixel);
    // icon size
    pEntitiesTreeWidget->setIconSize(QSize{GUIConfig::ICON_MIN_HEIGHT, GUIConfig::ICON_MIN_HEIGHT});
    // entitiesTreeWidget.setSpacing(GUIConfig::entityIconMinimumHeight * 0.1);

    connect(pEntitiesTreeWidget, &QTreeWidget::itemSelectionChanged, this, &HotkeysMainWindow::SetHotkeysPanelsWidget);

    //============================ Factions button group configure ============================
    QBoxLayout* factionsL = nullptr;
    int factonsCount = factionsManager.GetFactions().size();

    const int standartFactionsCount = 12;
    if (factonsCount == standartFactionsCount)
    {
        factionsL = new QHBoxLayout;

        // only 3 sections with factions and subfactions, 4 in each
        for (int sectionIndex = 0; sectionIndex < standartFactionsCount; sectionIndex += 4)
        {
            QVBoxLayout* currentFactionL = new QVBoxLayout;
            QHBoxLayout* currenSubfactionsL = new QHBoxLayout;

            for (int i = 0; i < 4; ++i)
            {
                const Faction currentFaction = factionsManager.GetFactions().at(sectionIndex + i);

                QPushButton* factionButton = new QPushButton{currentFaction.GetDisplayName()};

                connect(factionButton, &QPushButton::pressed, this, [=]()
                {
                    SetEntitiesList(currentFaction.GetShortName());
                });

                pFactionsButtonsGroup->addButton(factionButton);

                // main faction
                if (i == 0)
                {
                    currentFactionL->addWidget(factionButton);
                }
                // subfactions
                else
                {
                    currenSubfactionsL->addWidget(factionButton);
                }
            }

            currentFactionL->addLayout(currenSubfactionsL);
            factionsL->addLayout(currentFactionL);
        }
    }
    else
    {
        LOGMSG(QString("It has to be 12 factions. But it's: ") + QString::number(factonsCount));

        // TODO: not relevant
        // QHBoxLayout* firstL = new QHBoxLayout;
        // QHBoxLayout* secondL = new QHBoxLayout;

        // int i = 0;
        // for (const auto & faction : factions)
        // {
        //     QPushButton* factionButton = new QPushButton(QString::fromStdString(factions.at(i).DisplayName));
        //     if (i < factonsCount / 2)
        //     {
        //         firstL->addWidget(factionButton);
        //     }
        //     else
        //     {
        //         secondL->addWidget(factionButton);
        //     }
        //     ++i;
        // }

        // factionsL = new QVBoxLayout;
        // factionsL->addLayout(firstL);
        // factionsL->addLayout(secondL);
    }

    connect(pFactionsButtonsGroup, &QButtonGroup::idClicked, this, [=](int id)
    {
        // Take the focus from the buttons group
        pEntitiesTreeWidget->setFocus();

        // Select pressed faction button
        for (auto * button : pFactionsButtonsGroup->buttons())
        {
            if (button == pFactionsButtonsGroup->button(id))
            {
                button->setDown(true);
            }
            else
            {
                button->setDown(false);
            }
        }
    });

    //=========================================================================================

    // Fill all available space
    pHotkeysArea->setWidgetResizable(true);

    QVBoxLayout* buildingConfigurationL = new QVBoxLayout;
    buildingConfigurationL->addWidget(pHotkeysArea, 2);
    buildingConfigurationL->addWidget(new QScrollArea, 1);

    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->addWidget(pEntitiesTreeWidget, 4);
    contentL->addLayout(buildingConfigurationL, 7);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(factionsL);
    mainL->addLayout(contentL);

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);

    // Set start faction
    const auto firstFactionButton = pFactionsButtonsGroup->button(-2);
    if (firstFactionButton != nullptr) firstFactionButton->click();
}

void HotkeysMainWindow::ConfigureMenu()
{
    QMenu* mnFileOptions = new QMenu(tr("File"));
    mnFileOptions->addAction(tr("Special"));
    menuBar()->addMenu(mnFileOptions);
    menuBar()->addAction(tr("View"));

    QMenu* mnSettingsOptions = new QMenu(tr("Settings"));
    menuBar()->addMenu(mnSettingsOptions);

    QAction* actAbout = new QAction(tr("About"));
    connect(actAbout, &QAction::triggered, this, &HotkeysMainWindow::OnAbout);

    mnSettingsOptions->addAction(actAbout);
}

void HotkeysMainWindow::SetEntitiesList(const QString& factionShortName)
{
    pEntitiesTreeWidget->clear();

    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> factionEntities = factionsManager.GetFactionEntities(factionShortName);

    // Create sections for all faction entities types
    for (auto it = factionEntities.cbegin(); it != factionEntities.cend(); ++it)
    {
        const QVector<QSharedPointer<const Entity>>& currentTypeEntities = it.value();

        // Skip if there are no entities of that type
        if (currentTypeEntities.isEmpty()) continue;

        // Create new section of tree list
        QTreeWidgetItem* newTopEntityItem = new QTreeWidgetItem();
        newTopEntityItem->setText(0, QCoreApplication::translate("QObject", Config::ENTITIES_STRINGS.value(it.key()).toUtf8().constData()));

        // Decorate
        newTopEntityItem->setIcon(0, GUIConfig::getEntityTypePixmap(it.key()).scaledToHeight(GUIConfig::ICON_SCALING_HEIGHT,
                                                                                             Qt::SmoothTransformation));
        // newTopEntityItem->setBackground(0, QColor{0x73, 0xE9, 0xFF, 128});

        // Append entities to the section
        for (const auto & entity : currentTypeEntities)
        {
            QTreeWidgetItem* currentNewEntityItem = new QTreeWidgetItem();
            currentNewEntityItem->setText(0, entity->GetName());
            currentNewEntityItem->setIcon(0, QPixmap::fromImage(GUIConfig::decodeWebpIcon(entity->GetIconName())));
            currentNewEntityItem->setData(0, Qt::UserRole, QVariant::fromValue(QPair{factionShortName, entity->GetName()}));
            newTopEntityItem->addChild(currentNewEntityItem);
        }

        // Add section to the list
        pEntitiesTreeWidget->addTopLevelItem(newTopEntityItem);
    }

    // Configure view
    pEntitiesTreeWidget->expandAll();
    pEntitiesTreeWidget->scrollToTop();

    // Skip if missing top item
    const auto firstTopLevelItem = pEntitiesTreeWidget->topLevelItem(0);
    if (firstTopLevelItem == nullptr) return;

    // Skip if missing first entity
    const auto firstEntity = firstTopLevelItem->child(0);
    if (firstEntity == nullptr) return;

    // Set start entity
    pEntitiesTreeWidget->setCurrentItem(firstEntity);
}

void HotkeysMainWindow::SetHotkeysPanelsWidget()
{
    // Skip if there are no selected items
    if (pEntitiesTreeWidget->selectedItems().isEmpty()) return;

    // Current single selected item
    QTreeWidgetItem* item = pEntitiesTreeWidget->selectedItems().first();

    // Skip if it's the top level section item
    for (int i = 0; i < pEntitiesTreeWidget->topLevelItemCount(); ++i)
        if (item == pEntitiesTreeWidget->topLevelItem(i)) return;

    const QPair<QString, QString> specialItemInfo = item->data(0, Qt::UserRole).value<QPair<QString, QString>>();

    const QString& factionShortName = specialItemInfo.first;
    const QString& entityName = specialItemInfo.second;

    const QVector<QVector<QSharedPointer<EntityAction>>> entityPanels = factionsManager.GetEntityActionPanels(factionShortName, entityName);

    // Recreate panels widget
    if (pHotkeysPanelsWidget != nullptr) pHotkeysPanelsWidget->deleteLater();
    pHotkeysPanelsWidget = new QTabWidget();

    // Forget old hotkey widgets
    hotkeyWdgets.clear();

    // Panel index
    int i = 0;

    for (const auto & actionPanel : entityPanels)
    {
        QSet<ActionHotkeyWidget*> currentPanelWidgets;

        QVBoxLayout* hotkeysLayout = new QVBoxLayout();

        for (const auto & action : actionPanel)
        {
            ActionHotkeyWidget* actionHotkey = new ActionHotkeyWidget{action->GetName(), action->GetHotkey(), action->GetIconName()};

            // Remember widget
            currentPanelWidgets.insert(actionHotkey);

            connect(actionHotkey, &ActionHotkeyWidget::HotkeyChanged, this, [=](const QString& newHotkey)
            {
                // Set new hotkey
                factionsManager.SetEntityActionHotkey(factionShortName, entityName, action->GetName(), newHotkey);

                // Highlight keys for entity
                HighlightKeys(entityName);
            });

            hotkeysLayout->addWidget(actionHotkey);
        }

        // Remember hotkeys panel
        hotkeyWdgets.append(currentPanelWidgets);

        // Highlight keys for entity
        HighlightKeys(entityName);

        // Condense the actions at the top
        hotkeysLayout->addStretch(1);

        QWidget* panelScrollWidget = new QWidget;
        panelScrollWidget->setLayout(hotkeysLayout);
        pHotkeysPanelsWidget->addTab(panelScrollWidget, QString(tr("Layout %1")).arg(++i));
    }

    // If only one panel -> hide header
    if (pHotkeysPanelsWidget->count() <= 1) pHotkeysPanelsWidget->tabBar()->hide();

    pHotkeysPanelsWidget->setMinimumSize(pHotkeysPanelsWidget->sizeHint());
    pHotkeysArea->setWidget(pHotkeysPanelsWidget);
}

void HotkeysMainWindow::HighlightKeys(const QString& entityName) const
{
    // Skip if no widgets
    if (hotkeyWdgets.isEmpty()) return;

    // Change color if the current key is in collisions
    QVector<QSet<QString>> keysCollisions = factionsManager.GetEntityCollisionsKeys(entityName);

    // If no collisions
    if (keysCollisions.isEmpty())
    {
        // Unhighlight all keys and quit
        for (const auto & panel : hotkeyWdgets)
        {
            for (auto & hotkeyWidget : panel)
            {
                hotkeyWidget->HighlightKey(false);
            }
        }

        return;
    }

    // Panel index
    int i = -1;

    for (const auto & panel : hotkeyWdgets)
    {
        // Increase panel index
        ++i;

        for (auto & hotkeyWidget : panel)
        {
            if (keysCollisions.at(i).contains(hotkeyWidget->GetHotkey()))
            {
                hotkeyWidget->HighlightKey(true);
            }
            else
            {
                hotkeyWidget->HighlightKey(false);
            }
        }
    }
}

void HotkeysMainWindow::OnAbout()
{
    // if dialog already exists
    if (pAboutDialog != nullptr)
    {
        pAboutDialog->activateWindow();
        return;
    }

    QVBoxLayout* authorsL = new QVBoxLayout();
    authorsL->addWidget(new QLabel{tr("Authors: ") + AUTHORS});

    QGridLayout* contentL = new QGridLayout();
    contentL->addLayout(authorsL, 0, 0);
    QLabel* pixmap = new QLabel;
    pixmap->setPixmap(QPixmap::fromImage(GUIConfig::decodeDefaultWebpIcon()));
    contentL->addWidget(pixmap, 0, 1);
    QLabel* textL = new QLabel{tr("Program licensed by GNU GPL v3")};
    textL->setWordWrap(true);
    textL->setAlignment(Qt::AlignJustify);
    contentL->addWidget(textL, 1, 0);
    contentL->setSizeConstraint(QLayout::SetFixedSize);

    pAboutDialog = new QDialog{this};
    pAboutDialog->setWindowTitle(tr("About"));
    pAboutDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pAboutDialog->setWindowFlags(pAboutDialog->windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);

    connect(pAboutDialog, &QDialog::finished, this, [this]()
    {
        pAboutDialog->deleteLater();
        pAboutDialog = nullptr;
    });

    QDialogButtonBox* buttons = new QDialogButtonBox{QDialogButtonBox::Ok,
                                                     Qt::Orientation::Horizontal,
                                                     pAboutDialog};

    connect(buttons, &QDialogButtonBox::accepted, pAboutDialog, &QDialog::accept);

    QHBoxLayout* buttonsL = new QHBoxLayout();
    buttonsL->addStretch();
    buttons->button(QDialogButtonBox::Ok)->setFixedWidth(100);
    buttonsL->addWidget(buttons->button(QDialogButtonBox::Ok));
    buttonsL->addStretch();
    buttonsL->setAlignment(Qt::AlignCenter);

    QVBoxLayout* mainL = new QVBoxLayout();
    mainL->addLayout(contentL);
    mainL->addLayout(buttonsL);

    pAboutDialog->setLayout(mainL);
    pAboutDialog->show();
    pAboutDialog->raise();
    pAboutDialog->activateWindow();
}
