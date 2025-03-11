#include <QApplication>
#include <QMenuBar>
#include <QHeaderView>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QComboBox>

#include "../Parsers/CSFParser.hpp"
#include "../Info.hpp"
#include "../Logger.hpp"
#include "../NameOfExt.hpp"
#include "../Unsorted.hpp"
#include "../Convert.hpp"

#include "ImageManager.hpp"
#include "WindowManager.hpp"
#include "KeyboardLayout.hpp"
#include "SettingsWindow.hpp"
#include "EditorWindow.hpp"

EditorWindow::EditorWindow(QWidget* parent)
    : QMainWindow(parent)
    , pFactionsButtonsGroup{new QButtonGroup{this}}
    , pEntitiesTreeWidget{new QTreeWidget}
    , pHotkeysArea{new QScrollArea}
    , pHotkeysPanelsWidget{nullptr}
    , pAboutDialog{nullptr}
{
    SetFactions();
    LOGMSG("Total faction count that has been read from json file: " + factionVector.size());

    resize(1200, 800);
    ConfigureMenu();

    pEntitiesTreeWidget->header()->hide();
    // Enable smooth scrolling
    pEntitiesTreeWidget->setVerticalScrollMode(QTreeWidget::ScrollMode::ScrollPerPixel);
    // Set icon size
    pEntitiesTreeWidget->setIconSize(QSize{PROGRAM_CONSTANTS->ICON_MIN_HEIGHT, PROGRAM_CONSTANTS->ICON_MIN_HEIGHT});

    connect(pEntitiesTreeWidget, &QTreeWidget::itemSelectionChanged, this, &EditorWindow::SetHotkeysPanels);

    QBoxLayout* ltFactions = nullptr;
    int factonsCount = factionVector.size();

    if (factonsCount == Faction::BASIC_FACTION_COUNT)
    {
        ltFactions = new QHBoxLayout();
        ltFactions->setObjectName(nameof(ltFactions));

        // only 3 sections with factions and subfactions, 4 in each
        for (int sectionIndex = 0; sectionIndex < Faction::BASIC_FACTION_COUNT; sectionIndex += 4)
        {
            QVBoxLayout* ltCurrentFaction    = new QVBoxLayout();
            QHBoxLayout* ltCurrentSubfaction = new QHBoxLayout();
            ltCurrentFaction->setObjectName(nameof(ltCurrentFaction));
            ltCurrentSubfaction->setObjectName(nameof(ltCurrentSubfaction));

            for (int i = 0; i < 4; ++i)
            {
                const Faction currFaction = factionVector.at(sectionIndex + i);

                QPushButton* factionButton = new QPushButton{currFaction.GetDisplayName()};

                auto shortName = currFaction.GetShortName();
                if (PROGRAM_CONSTANTS->USA_SHORT_NAMES.contains(shortName))
                factionButton->setProperty("faction", "USA");

                if (PROGRAM_CONSTANTS->PRC_SHORT_NAMES.contains(shortName))
                    factionButton->setProperty("faction", "PRC");

                if (PROGRAM_CONSTANTS->GLA_SHORT_NAMES.contains(shortName))
                    factionButton->setProperty("faction", "GLA");

                connect(factionButton, &QPushButton::pressed, this, [=, this]()
                {
                    SetGameObjectList(shortName);
                });

                pFactionsButtonsGroup->addButton(factionButton);

                if (i == 0) // main faction
                    ltCurrentFaction->addWidget(factionButton);
                else        // subfactions
                    ltCurrentSubfaction->addWidget(factionButton);
            }

            ltCurrentFaction->addLayout(ltCurrentSubfaction);
            ltFactions->addLayout(ltCurrentFaction);
        }
    }
    else
    {
        LOGMSG("Unable to parse more than 12 factions. Found factions : " + factonsCount);
    }

    connect(pFactionsButtonsGroup, &QButtonGroup::idClicked, this, [=, this](int id)
    {
        // Take the focus from the buttons group
        pEntitiesTreeWidget->setFocus();

        // Select pressed faction button
        for (auto* button : pFactionsButtonsGroup->buttons())
        {
            if (button == pFactionsButtonsGroup->button(id))
                button->setDown(true);
            else
                button->setDown(false);
        }
    });

    // Fill all available space
    pHotkeysArea->setWidgetResizable(true);

    // Draw keyboard with letters
    pKeyboardLayout = new KeyboardLayout();
    QScrollArea* pKeyboardWindow = new QScrollArea();
    pKeyboardWindow->setObjectName("Keyboard");
    pKeyboardWindow->setLayout(pKeyboardLayout);

    QVBoxLayout* ltGameObject = new QVBoxLayout();
    ltGameObject->addWidget(pHotkeysArea, 2);
    ltGameObject->addWidget(pKeyboardWindow, 1);

    QHBoxLayout* ltContent = new QHBoxLayout();
    ltContent->addWidget(pEntitiesTreeWidget, 4);
    ltContent->addLayout(ltGameObject, 7);

    QVBoxLayout* ltMain = new QVBoxLayout();
    ltMain->addLayout(ltFactions);
    ltMain->addLayout(ltContent);

    // Main widget
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(ltMain);
    setCentralWidget(centralWidget);

    // Set start faction
    const auto firstFactionButton = pFactionsButtonsGroup->button(-2); // Magic number equals to begining of the array of the all buttons.
    if (firstFactionButton != nullptr) firstFactionButton->click();
}

void EditorWindow::ConfigureMenu()
{
    QMenu* mnFileOptions = new QMenu(tr("File"));
    QAction* actOpen     = new QAction(tr("Open"));
    QAction* actSave     = new QAction(tr("Save"));
    QAction* actSaveAs   = new QAction(tr("Save As..."));
    QAction* actSpecial  = new QAction(tr("Special"));
    mnFileOptions->addAction(actOpen);
    mnFileOptions->addAction(actSave);
    mnFileOptions->addAction(actSaveAs);
    mnFileOptions->addAction(actSpecial);
    menuBar()->addMenu(mnFileOptions);

    connect(actOpen, &QAction::triggered, this, &EditorWindow::ActOpen_Triggered);
    connect(actSave, &QAction::triggered, this, &EditorWindow::ActSave_Triggered);
    connect(actSaveAs, &QAction::triggered, this, &EditorWindow::ActSaveAs_Triggered);

    QMenu* mnViewOptions = new QMenu(tr("View"));
    QMenu* mnStatusBarChecbox = new QMenu(tr("Status Bar"));
    mnStatusBarChecbox->addAction(tr("Enable"));
    mnStatusBarChecbox->addAction(tr("Disable"));
    mnViewOptions->addMenu(mnStatusBarChecbox);
    menuBar()->addMenu(mnViewOptions);
   
    QAction* actSettings = new QAction(tr("Settings"));
    connect(actSettings, &QAction::triggered, this, &EditorWindow::ActSettings_Triggered);
    menuBar()->addAction(actSettings);

    QAction* actAbout = new QAction(tr("About"));
    connect(actAbout, &QAction::triggered, this, &EditorWindow::ActAbout_Triggered);
    menuBar()->addAction(actAbout);
}

void EditorWindow::SetGameObjectList(const QString& factionShortName)
{
    pEntitiesTreeWidget->clear();

    QMap<Faction::GameObject, GameObjectTypes> goMap = GetFactionRef(factionShortName).GetTechTree();

    // Skip if there are no entities of that type
    if(goMap.isEmpty()) return;

    // Create sections for all faction entities types
    for(const auto& objectType : PROGRAM_CONSTANTS->INGAME_ENTITIES_STRINGS.keys())
    {
        // Create new section of tree list
        QTreeWidgetItem* newTopEntityItem = new QTreeWidgetItem();
        newTopEntityItem->setText(0, L10N(PROGRAM_CONSTANTS->INGAME_ENTITIES_STRINGS.value(objectType)));

        // Decorate
        newTopEntityItem->setIcon(0, ImageManager::GetGameObjectTypePixmap(objectType)
                                               .scaledToHeight(PROGRAM_CONSTANTS->ICON_SCALING_HEIGHT, Qt::SmoothTransformation));

        // If there no objects by type - then skip
        if (goMap.keys(objectType).isEmpty()) continue;
        
        // Append entities to the section
        for (const auto& go : goMap.keys(objectType))
        {
            QTreeWidgetItem* currentNewEntityItem = new QTreeWidgetItem();
            currentNewEntityItem->setText(0, CSF_PARSER->GetStringValue(go.ingameName));
            currentNewEntityItem->setIcon(0, QPixmap::fromImage(ImageManager::DecodeWebpIcon(go.iconName)));
            currentNewEntityItem->setData(0, Qt::UserRole, QVariant::fromValue(QPair{factionShortName, go.iconName}));
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

void EditorWindow::SetHotkeysPanels()
{
    // Skip if there are no selected items
    if (pEntitiesTreeWidget->selectedItems().isEmpty()) return;

    // Current single selected item
    QTreeWidgetItem* pItem = pEntitiesTreeWidget->selectedItems().first();

    // Skip if it's the top level section item
    for (int i = 0; i < pEntitiesTreeWidget->topLevelItemCount(); ++i)
        if (pItem == pEntitiesTreeWidget->topLevelItem(i)) return;

    const QPair<QString, QString> specialItemInfo = pItem->data(0, Qt::UserRole).value<QPair<QString, QString>>();

    const QString& factionShortName = specialItemInfo.first;
    const QString& gameObjectName   = specialItemInfo.second;

    const auto gameObjectKeyboardLayouts = GetFactionRef(factionShortName).GetKeyboardLayoutsByObjectName(gameObjectName);

    // Recreate panels widget
    if (pHotkeysPanelsWidget != nullptr) pHotkeysPanelsWidget->deleteLater();
    pHotkeysPanelsWidget = new QTabWidget();

    // Forget old hotkey widgets
    vHotkeyWidgets.clear();

    // Panel index
    int i = 0;
    
    for (const auto& currLayout : gameObjectKeyboardLayouts)
    {
        QSet<ActionHotkeyWidget*> currentPanelWidgets;
        QVBoxLayout* ltHotkeys = new QVBoxLayout();

        for (const auto& currAction : currLayout)
        {
            ActionHotkeyWidget* actionHotkey = new ActionHotkeyWidget{CSF_PARSER->GetClearName(currAction.hotkeyString), 
                                                                      CSF_PARSER->GetHotkey(currAction.hotkeyString),
                                                                      currAction.iconName};

            // TODO: Make it dynamic
            actionHotkey->setToolTip(currAction.hotkeyString + "\n\n" + CSF_PARSER->GetStringValue(currAction.hotkeyString));

            connect(actionHotkey, &ActionHotkeyWidget::HotkeyChanged, this, [=, this](const QString& newHotkey)
            {
                // Set new hotkey
                SetActionHotkey(factionShortName, gameObjectName, currAction.iconName, newHotkey);

                // Highlight keys for entity
                HighlightCurrentKeys();

                emit pHotkeysPanelsWidget->currentChanged(i);
            });

            ltHotkeys->addWidget(actionHotkey);

            // Remember widget
            currentPanelWidgets.insert(actionHotkey);
        }

        // Remember hotkeys panel
        vHotkeyWidgets.append(currentPanelWidgets);

        // Highlight keys for entity
        HighlightCurrentKeys();

        // Condense the actions at the top with minumum spacing
        ltHotkeys->setAlignment(Qt::AlignTop);
        ltHotkeys->setSpacing(0);

        QWidget* panelScrollWidget = new QWidget();
        panelScrollWidget->setLayout(ltHotkeys);
        panelScrollWidget->setObjectName(QString("Layout ") + QString::number(i+1));
        pHotkeysPanelsWidget->addTab(panelScrollWidget, QString(tr("Layout %1")).arg(++i));
    }

    // If only one panel -> hide header
    if (pHotkeysPanelsWidget->count() < 2) pHotkeysPanelsWidget->tabBar()->hide();

    pHotkeysPanelsWidget->setMinimumSize(pHotkeysPanelsWidget->sizeHint());
    pHotkeysArea->setWidget(pHotkeysPanelsWidget);

    connect(pHotkeysPanelsWidget, &QTabWidget::currentChanged, this, [this](int id){ pKeyboardLayout->Update(*pHotkeysPanelsWidget, id);});

    emit pHotkeysPanelsWidget->currentChanged(0);
}

void EditorWindow::HighlightCurrentKeys()
{
    // Skip if no widgets
    if (vHotkeyWidgets.isEmpty()) return;

    // Else code does check for collisions
    for (auto& panel : vHotkeyWidgets)
    {
        // Fill list with only letters of keys
        QList<QString> keysCollisions;
        for (const auto& hotkeyWidget: panel)
            keysCollisions.push_back(hotkeyWidget->GetHotkey());

        for (auto& hotkeyWidget : panel)
        {
            const QString& thisHotkey = hotkeyWidget->GetHotkey();

            if (keysCollisions.count(thisHotkey) < 2) hotkeyWidget->HighlightKey(false);
            else                                      hotkeyWidget->HighlightKey(true);

            if (!PROGRAM_CONSTANTS->pSettingsFile->GetAllowedKeys().contains(Convert::ToQtKey(thisHotkey[0])))
                hotkeyWidget->HighlightKey(true);
        }
    }
}

void EditorWindow::SetFactions()
{
    for(const auto& elem : TECH_TREE_SOURCE.Query("$.TechTree").toArray())
        factionVector.push_back(Faction{elem.toObject()});
}

const Faction& EditorWindow::GetFactionRef(const QString& name)
{
    int tmp = 0;

    for(int i = 0; i < factionVector.count(); i++)
    {
        const Faction& elem = factionVector[i];
        
        if(elem.GetShortName() == name)
        {
            tmp = i;
            break;
        }
    }
    
    return factionVector.at(tmp);
}

void EditorWindow::SetActionHotkey(const QString& fctShortName, const QString& goName, const QString& actName, const QString& hk)
{
    for(Faction& fct : factionVector)
    {
        if(fct.GetShortName() == fctShortName)
        {
            fct.SetHotkey(goName, actName, hk);
            break;
        }
    }
}

void EditorWindow::ActAbout_Triggered()
{
    // if dialog already exists
    if (pAboutDialog != nullptr)
    {
        pAboutDialog->activateWindow();
        return;
    }
    QGridLayout* lblContent = new QGridLayout();
    lblContent->setSizeConstraint(QLayout::SetFixedSize);
        
    QLabel* lblAboutText = new QLabel
    {
        QString("<p>") 
        + tr("Authors: ") + AUTHORS + "<br>"
        + tr("Version: ") + VERSION + "<br><br>"
        + tr("Program licensed with ") + "<a style=\"color: #baff0c;\" href=\"https://github.com/MahBoiDeveloper/GZHHotkeysEditor/blob/main/LICENSE\">GNU GPL v3</a><br><br>" 
        + tr("GitHub repository:") + "<br>"
        + "<a style=\"color: #baff0c;\" href=\"https://github.com/MahBoiDeveloper/GZHHotkeysEditor\">github.com/MahBoiDeveloper/GZHHotkeysEditor</a><br><br>"
        + tr("Support development:") + "<br>"
        + "<a style=\"color: #baff0c;\" href=\"https://boosty.to/mah_boi\">boosty.to/mah_boi</a></p>"
    };
    lblAboutText->setObjectName("left");
    lblAboutText->setTextFormat(Qt::RichText);
    lblAboutText->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lblAboutText->setOpenExternalLinks(true);
    lblContent->addWidget(lblAboutText, 0, 0);
    
    QLabel* lblEditorIcon = new QLabel();
    lblEditorIcon->setPixmap(QPixmap::fromImage(ImageManager::DecodeBigEditorWebpIcon()));
    lblEditorIcon->setObjectName("right");
    lblContent->addWidget(lblEditorIcon, 0, 1);

    pAboutDialog = new QDialog{this};
    pAboutDialog->setWindowTitle(tr("About"));
    pAboutDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pAboutDialog->setWindowFlags(pAboutDialog->windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);

    QVBoxLayout* ltMainBlock = new QVBoxLayout();
    ltMainBlock->addLayout(lblContent);

    pAboutDialog->setLayout(ltMainBlock);
    pAboutDialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    pAboutDialog->show();
    pAboutDialog->activateWindow();
    
    connect(pAboutDialog, &QDialog::finished, this, [this]()
    {
        pAboutDialog->deleteLater();
        pAboutDialog = nullptr;
    });
}

void EditorWindow::ActSettings_Triggered()
{
    if (pSettingsWindow == nullptr)
    {
        // Read this thread: 
        //    https://forum.qt.io/topic/146107/can-t-show-the-border-of-the-class-inheriting-qwidget-class
        // to understand why QWidget's inherited class has been wrapped into another native QWidget

        auto sw         = new SettingsWindow();
        auto lt         = new QVBoxLayout();
        lt->addWidget(sw);

        pSettingsWindow = new QWidget();
        pSettingsWindow->setObjectName(nameof(pSettingsWindow));
        pSettingsWindow->setWindowTitle(tr("Settings"));
        pSettingsWindow->setFixedSize(PROGRAM_CONSTANTS->SET_UP_WINDOW_SIZE);
        pSettingsWindow->setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
        pSettingsWindow->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint
                                                      & ~Qt::WindowMinimizeButtonHint);
        pSettingsWindow->setWindowModality(Qt::WindowModality::ApplicationModal);
        pSettingsWindow->setLayout(lt);
    }

    pSettingsWindow->show();
}

void EditorWindow::ActSave_Triggered()
{
    LOGMSG("Saving changes to .csf file...");
    CSF_PARSER->Save();
    LOGMSG("Changes has been saved");
}

void EditorWindow::ActSaveAs_Triggered()
{
}

void EditorWindow::ActOpen_Triggered()
{
}
