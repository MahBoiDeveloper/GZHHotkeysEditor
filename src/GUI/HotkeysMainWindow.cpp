#include <QMenuBar>
#include <QHeaderView>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QScrollArea>

#include "../Parsers/CSFParser.hpp"
#include "../Info.hpp"
#include "../Logger.hpp"

#include "ActionHotkeyWidget.hpp"
#include "GUIConfig.hpp"
#include "HotkeysMainWindow.hpp"
#include "WindowManager.hpp"

HotkeysMainWindow::HotkeysMainWindow(const QVariant& configuration, QWidget* parent)
    : QMainWindow(parent)
    , pFactionsButtonsGroup{new QButtonGroup{this}}
    , pEntitiesTreeWidget{new QTreeWidget}
    , pHotkeysArea{new QScrollArea}
    , pKeyboardWindow{new QScrollArea}
    , pHotkeysPanelsWidget{nullptr}
    , pAboutDialog{nullptr}
{
    SetFactions();
    LOGMSG(QString{"Total faction count that has been read from json file: "} + QString::number(factionVector.size()));

    resize(1200, 800);
    ConfigureMenu();

    pEntitiesTreeWidget->header()->hide();
    // Enable smooth scrolling
    pEntitiesTreeWidget->setVerticalScrollMode(QTreeWidget::ScrollMode::ScrollPerPixel);
    // Set icon size
    pEntitiesTreeWidget->setIconSize(QSize{GUIConfig::ICON_MIN_HEIGHT, GUIConfig::ICON_MIN_HEIGHT});
    // entitiesTreeWidget.setSpacing(GUIConfig::entityIconMinimumHeight * 0.1);

    connect(pEntitiesTreeWidget, &QTreeWidget::itemSelectionChanged, this, &HotkeysMainWindow::SetHotkeysPanelsWidget);

    QBoxLayout* ltFactions = nullptr;
    int factonsCount = factionVector.size();

    if (factonsCount == Faction::BASIC_FACTION_COUNT)
    {
        ltFactions = new QHBoxLayout();

        // only 3 sections with factions and subfactions, 4 in each
        for (int sectionIndex = 0; sectionIndex < Faction::BASIC_FACTION_COUNT; sectionIndex += 4)
        {
            QVBoxLayout* ltCurrentFaction    = new QVBoxLayout();
            QHBoxLayout* ltCurrentSubfaction = new QHBoxLayout();

            for (int i = 0; i < 4; ++i)
            {
                const Faction currFaction = factionVector.at(sectionIndex + i);
                
                QPushButton* factionButton = new QPushButton{currFaction.GetDisplayName()};
                
                auto shortName = currFaction.GetShortName();
                if (shortName == "USA" || 
                    shortName == "SWG" ||
                    shortName == "AIR" ||
                    shortName == "LSR")
                    ;

                if (shortName == "PRC" || 
                    shortName == "TNK" ||
                    shortName == "INF" ||
                    shortName == "NUK")
                    factionButton->setProperty("faction", "PRC");
                
                if (shortName == "GLA" || 
                    shortName == "TOX" ||
                    shortName == "STL" ||
                    shortName == "DML")
                    factionButton->setProperty("faction", "GLA");

                connect(factionButton, &QPushButton::pressed, this, [=]()
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
        LOGMSG(QString("Unable to parse more than 12 factions. Found factions : ") + QString::number(factonsCount));
    }

    connect(pFactionsButtonsGroup, &QButtonGroup::idClicked, this, [=](int id)
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
    pKeyboardWindow->setObjectName("Keyboard");
    QHBoxLayout* pKeyboardFirstLine  = new QHBoxLayout(); pKeyboardFirstLine->setAlignment(Qt::AlignHCenter);
    QHBoxLayout* pKeyboardSecondLine = new QHBoxLayout(); pKeyboardSecondLine->setAlignment(Qt::AlignHCenter);
    QHBoxLayout* pKeyboardThirdLine  = new QHBoxLayout(); pKeyboardThirdLine->setAlignment(Qt::AlignHCenter);
    QVBoxLayout* pKeyboardLines      = new QVBoxLayout();
    
    QPushButton* btnEmptyButton= new QPushButton();
    btnEmptyButton->setProperty("key", "null");
    btnEmptyButton->setFixedWidth(GUIConfig::EMTPTY_KEY_WIDTH);

    // TODO :
    //      Make it in different fucntion
    // Set 1st line of keys
    for (const auto& ch : QString("QWERTYUIOP"))
    {
        auto tmp = new QPushButton(ch);
        tmp->setProperty("key", ch);
        tmp->setObjectName(ch);
        tmp->setFixedWidth(GUIConfig::KEYBOARD_KEY_WIDTH);
        pKeyboardFirstLine->addWidget(tmp);
    }

    // Set 2nd line of keys
    for (const auto& ch : QString("ASDFGHJKL"))
    {
        auto tmp = new QPushButton(ch);
        tmp->setProperty("key", ch);
        tmp->setObjectName(ch);
        tmp->setFixedWidth(GUIConfig::KEYBOARD_KEY_WIDTH);
        pKeyboardSecondLine->addWidget(tmp);
    }
    
    // Set 3rd line of keys
    for (const auto& ch : QString("ZXCVBNM"))
    {
        auto tmp = new QPushButton(ch);
        tmp->setProperty("key", ch);
        tmp->setObjectName(ch);
        tmp->setFixedWidth(GUIConfig::KEYBOARD_KEY_WIDTH);
        pKeyboardThirdLine->addWidget(tmp);
    }
    pKeyboardThirdLine->addWidget(btnEmptyButton);

    pKeyboardLines->addLayout(pKeyboardFirstLine);
    pKeyboardLines->addLayout(pKeyboardSecondLine);
    pKeyboardLines->addLayout(pKeyboardThirdLine);

    pKeyboardWindow->setLayout(pKeyboardLines);

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

void HotkeysMainWindow::ConfigureMenu()
{
    QMenu* mnFileOptions = new QMenu(tr("File"));
    mnFileOptions->addAction(tr("Special"));
    menuBar()->addMenu(mnFileOptions);
    menuBar()->addAction(tr("View"));

    QMenu* mnSettingsOptions = new QMenu(tr("Settings"));
    menuBar()->addMenu(mnSettingsOptions);
    
    QAction* actLanguage = new QAction(tr("Language"));
    connect(actLanguage, &QAction::triggered, this, &HotkeysMainWindow::OnLanguageChange);
    mnSettingsOptions->addAction(actLanguage);

    QAction* actAbout = new QAction(tr("About"));
    connect(actAbout, &QAction::triggered, this, &HotkeysMainWindow::OnAbout);
    mnSettingsOptions->addAction(actAbout);
}

void HotkeysMainWindow::SetGameObjectList(const QString& factionShortName)
{
    pEntitiesTreeWidget->clear();

    QMap<Faction::GameObject, Config::GameObjectTypes> goMap = GetFactionRef(factionShortName).GetTechTree();

    // Skip if there are no entities of that type
    if(goMap.isEmpty()) return;

    // Create sections for all faction entities types
    for(const auto& objectType : Config::ENTITIES_STRINGS.keys())
    {
        // Create new section of tree list
        QTreeWidgetItem* newTopEntityItem = new QTreeWidgetItem();
        newTopEntityItem->setText(0, QCoreApplication::translate("QObject", Config::ENTITIES_STRINGS.value(objectType).toUtf8().constData()));

        // Decorate
        newTopEntityItem->setIcon(0, GUIConfig::GetGameObjectTypePixmap(objectType)
                                               .scaledToHeight(GUIConfig::ICON_SCALING_HEIGHT, Qt::SmoothTransformation));

        // If there no objects by type - then skip
        if (goMap.keys(objectType).isEmpty()) continue;
        
        // Append entities to the section
        for (const auto& go : goMap.keys(objectType))
        {
            QTreeWidgetItem* currentNewEntityItem = new QTreeWidgetItem();
            currentNewEntityItem->setText(0, CSF_PARSER->GetStringValue(go.ingameName));
            currentNewEntityItem->setIcon(0, QPixmap::fromImage(GUIConfig::DecodeWebpIcon(go.iconName)));
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

void HotkeysMainWindow::SetHotkeysPanelsWidget()
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
        QVBoxLayout* hotkeysLayout = new QVBoxLayout();

        for (const auto& currAction : currLayout)
        {
            ActionHotkeyWidget* actionHotkey = new ActionHotkeyWidget{CSF_PARSER->GetClearName(currAction.hotkeyString), 
                                                                      QString::fromStdWString(std::wstring{CSF_PARSER->GetHotkey(currAction.hotkeyString)}),
                                                                      currAction.iconName};

            // Remember widget
            currentPanelWidgets.insert(actionHotkey);

            connect(actionHotkey, &ActionHotkeyWidget::HotkeyChanged, this, [=](const QString& newHotkey)
            {
                // Set new hotkey
                SetActionHotkey(factionShortName, gameObjectName, currAction.iconName, newHotkey);

                // Highlight keys for entity
                HighlightCurrentKeys();

                emit pHotkeysPanelsWidget->currentChanged(i);
            });

            hotkeysLayout->addWidget(actionHotkey);
        }

        // Remember hotkeys panel
        vHotkeyWidgets.append(currentPanelWidgets);

        // Highlight keys for entity
        HighlightCurrentKeys();

        // Condense the actions at the top
        hotkeysLayout->addStretch(1);

        QWidget* panelScrollWidget = new QWidget();
        panelScrollWidget->setLayout(hotkeysLayout);
        panelScrollWidget->setObjectName(QString("Layout ") + QString::number(i+1));
        pHotkeysPanelsWidget->addTab(panelScrollWidget, QString(tr("Layout %1")).arg(++i));
    }

    // If only one panel -> hide header
    if (pHotkeysPanelsWidget->count() < 2) pHotkeysPanelsWidget->tabBar()->hide();

    pHotkeysPanelsWidget->setMinimumSize(pHotkeysPanelsWidget->sizeHint());
    pHotkeysArea->setWidget(pHotkeysPanelsWidget);

    connect(pHotkeysPanelsWidget, &QTabWidget::currentChanged, this, &HotkeysMainWindow::UpdateKeyboardStatus);

    emit pHotkeysPanelsWidget->currentChanged(0);
}

void HotkeysMainWindow::HighlightCurrentKeys()
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
        }
    }
}

void HotkeysMainWindow::NullifyKeyboardStatus()
{
    for (QChar& qc : QString("QWERTYUIOPASDFGHJKLZXCVBNM")) 
    {
        auto key = pKeyboardWindow->findChild<QPushButton*>(qc, Qt::FindChildrenRecursively);
        key->setProperty("status", "null");
        key->style()->unpolish(key);
        key->style()->polish(key);
        key->update();
    }
}

void HotkeysMainWindow::UpdateKeyboardStatus(int id)
{
    NullifyKeyboardStatus();
    auto currTab = pHotkeysPanelsWidget->findChild<QWidget*>(QString("Layout ") + QString::number(id + 1), Qt::FindChildrenRecursively);
        
    QString accum;
    for (const auto& elem : currTab->findChildren<ActionHotkeyWidget*>(QString(), Qt::FindChildrenRecursively))
        accum += QString(elem->GetHotkey());

    for (const QChar& ch : accum)
    {
        auto key = pKeyboardWindow->findChild<QPushButton*>(ch, Qt::FindChildrenRecursively);

        if (accum.count(ch) < 2) key->setProperty("status", "good");
        else                     key->setProperty("status", "bad");
        
        key->style()->unpolish(key);
        key->style()->polish(key);
        key->update();
    }
}

void HotkeysMainWindow::SetFactions()
{
    for(const auto& elem : TECH_TREE_SOURCE.Query("$.TechTree").toArray())
        factionVector.push_back(Faction{elem.toObject()});
}

const Faction& HotkeysMainWindow::GetFactionRef(const QString& name)
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

void HotkeysMainWindow::SetActionHotkey(const QString& fctShortName, const QString& goName, const QString& actName, const QString& hk)
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

void HotkeysMainWindow::OnAbout()
{
    // if dialog already exists
    if (pAboutDialog != nullptr)
    {
        pAboutDialog->activateWindow();
        return;
    }
    QGridLayout* lblContent = new QGridLayout();
    lblContent->setSizeConstraint(QLayout::SetFixedSize);
        
    QLabel* lblAboutText = new QLabel{QString("<p>") 
                                        + tr("Authors: ") + AUTHORS + "<br>"
                                        + tr("Version: ") + VERSION + "<br><br>"
                                        + tr("Program licensed with ") + "<a style=\"color: #baff0c;\" href=\"https://github.com/MahBoiDeveloper/GZHHotkeysEditor/blob/main/LICENSE\">GNU GPL v3</a><br><br>" 
                                        + tr("GitHub repository:") + "<br>"
                                        + "<a style=\"color: #baff0c;\" href=\"https://github.com/MahBoiDeveloper/GZHHotkeysEditor\">github.com/MahBoiDeveloper/GZHHotkeysEditor</a><br><br>"
                                        + tr("Support development:") + "<br>"
                                        + "<a style=\"color: #baff0c;\" href=\"https://boosty.to/mah_boi\">boosty.to/mah_boi</a></p>"};
    lblAboutText->setObjectName("left");
    lblAboutText->setTextFormat(Qt::RichText);
    lblAboutText->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lblAboutText->setOpenExternalLinks(true);
    lblContent->addWidget(lblAboutText, 0, 0);
    
    QLabel* lblEditorIcon = new QLabel();
    lblEditorIcon->setPixmap(QPixmap::fromImage(GUIConfig::DecodeBigEditorWebpIcon()));
    lblEditorIcon->setObjectName("right");
    lblContent->addWidget(lblEditorIcon, 0, 1);

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

    QVBoxLayout* ltMainBlock = new QVBoxLayout();
    ltMainBlock->addLayout(lblContent);

    pAboutDialog->setLayout(ltMainBlock);
    pAboutDialog->show();
    pAboutDialog->raise();
    pAboutDialog->activateWindow();
}

void HotkeysMainWindow::OnLanguageChange()
{
    QDialog* pWindowToChangeLanugage = new QDialog{this};
    pWindowToChangeLanugage->setWindowTitle(tr("Lanugage"));
    pWindowToChangeLanugage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pWindowToChangeLanugage->setWindowFlags(pWindowToChangeLanugage->windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);

    pWindowToChangeLanugage->show();
    pWindowToChangeLanugage->raise();
    pWindowToChangeLanugage->activateWindow();
}
