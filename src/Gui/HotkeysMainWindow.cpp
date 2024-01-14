#include <QMenuBar>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>

#include "../Info.hpp"
#include "../Logger.hpp"
#include "../Parsers/TechTreeJsonParser.hpp"
#include "../Parsers/CSFParser.hpp"
#include "HotkeysMainWindow.hpp"
#include "ActionHotkeyWidget.hpp"
#include "GUIConfig.hpp"

HotkeysMainWindow::HotkeysMainWindow(const QVariant& configuration, QWidget* parent)
    : QMainWindow(parent)
    , factions{TechTreeJsonParser::GetFactions()}
    , factionsButtonsGroup{}
    , entitiesTreeWidget{new QTreeWidget}
    , hotkeysArea{new QScrollArea}
    , hotkeysScrollWidget{nullptr}
    , aboutDialog{nullptr}
{
    resize(1200, 800);

    configureMenu();

    //============================ Entities Tree Widget configure =============================

    entitiesTreeWidget->header()->hide();
    // smooth scrolling
    entitiesTreeWidget->setVerticalScrollMode(QListWidget::ScrollMode::ScrollPerPixel);
    // icon size
    entitiesTreeWidget->setIconSize(QSize{GUIConfig::entityIconMinimumHeight, GUIConfig::entityIconMinimumHeight});
//    entitiesTreeWidget.setSpacing(GUIConfig::entityIconMinimumHeight * 0.1);

    //============================ Factions button group configure ============================
    QBoxLayout* factionsL = nullptr;
    int factonsCount = factions.size();

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
                const Faction currentFaction = factions.at(sectionIndex + i);

                QPushButton* factionButton = new QPushButton{currentFaction.getDisplayName()};

                connect(factionButton, &QPushButton::pressed, this, [=]()
                {
                    setEntitiesList(currentFaction.getShortName());
                });

                factionsButtonsGroup.addButton(factionButton);

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
        LOGSTM << "It has to be 12 factions. But it's: " << factonsCount;

        // TODO: not relevant
//        QHBoxLayout* firstL = new QHBoxLayout;
//        QHBoxLayout* secondL = new QHBoxLayout;

//        int i = 0;
//        for (const auto & faction : factions)
//        {
//            QPushButton* factionButton = new QPushButton(QString::fromStdString(factions.at(i).DisplayName));
//            if (i < factonsCount / 2)
//            {
//                firstL->addWidget(factionButton);
//            }
//            else
//            {
//                secondL->addWidget(factionButton);
//            }
//            ++i;
//        }

//        factionsL = new QVBoxLayout;
//        factionsL->addLayout(firstL);
//        factionsL->addLayout(secondL);
    }

    connect(entitiesTreeWidget, &QTreeWidget::itemSelectionChanged, this, &HotkeysMainWindow::setHotkeysLayout);

    //=========================================================================================

    // Fill all available space
    hotkeysArea->setWidgetResizable(true);

    QVBoxLayout* buildingConfigurationL = new QVBoxLayout;
    buildingConfigurationL->addWidget(hotkeysArea, 2);
    buildingConfigurationL->addWidget(new QScrollArea, 1);

    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->addWidget(entitiesTreeWidget, 4);
    contentL->addLayout(buildingConfigurationL, 7);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(factionsL);
    mainL->addLayout(contentL);

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);

    connect(&factionsButtonsGroup, &QButtonGroup::idClicked, this, [=](int)
    {
        // Skip if missing
        const auto firstTopLevelItem = entitiesTreeWidget->topLevelItem(0);
        if (firstTopLevelItem == nullptr) return;

        // Skip if missing
        const auto firstEntity = firstTopLevelItem->child(0);
        if (firstEntity == nullptr) return;

        // Set start entity
        entitiesTreeWidget->setCurrentItem(firstEntity);
        entitiesTreeWidget->setFocus();
    });

    // Set start faction
    const auto firstFactionButton = factionsButtonsGroup.buttons().first();
    if (firstFactionButton != nullptr) firstFactionButton->click();
}

void HotkeysMainWindow::configureMenu()
{
    QMenu* fm = new QMenu(tr("File"));
    fm->addAction(tr("Special"));
    menuBar()->addMenu(fm);
    menuBar()->addAction(tr("View"));
    QMenu* settingsM = new QMenu(tr("Settings"));
    menuBar()->addMenu(settingsM);
    QAction* aboutA = new QAction(tr("About"));
    connect(aboutA, &QAction::triggered, this, &HotkeysMainWindow::onAbout);
    settingsM->addAction(aboutA);
}

void HotkeysMainWindow::setEntitiesList(const QString& factionShortName)
{
    entitiesTreeWidget->clear();

    for (auto it = Config::ENTITIES_STRINGS.cbegin(); it != Config::ENTITIES_STRINGS.cend(); ++it)
    {
        QVector<Entity> currentTypeEntities = TechTreeJsonParser::getFactionEntities(it.key(), factionShortName);

        // Skip if there are no entities of that type
        if (currentTypeEntities.isEmpty()) continue;

        // Create new section of tree list
        QTreeWidgetItem* newTopEntityItem = new QTreeWidgetItem;
        newTopEntityItem->setText(0, it.value());
        // Decorate
        newTopEntityItem->setBackground(0, QColor{0x73, 0xE9, 0xFF, 128});

        // Append entities to the section
        for (const auto & entity : currentTypeEntities)
        {
            QTreeWidgetItem* currentNewEntityItem = new QTreeWidgetItem;
            currentNewEntityItem->setText(0, CSFPARSER->GetStringValue(entity.getIngameName()));
            currentNewEntityItem->setIcon(0, QPixmap::fromImage(GUIConfig::decodeWebpIcon(entity.getName())));
            currentNewEntityItem->setData(0, Qt::UserRole, QVariant::fromValue(QPair{factionShortName, entity.getName()}));
            newTopEntityItem->addChild(currentNewEntityItem);
        }

        // Add section to the list
        entitiesTreeWidget->addTopLevelItem(newTopEntityItem);
    }

    entitiesTreeWidget->expandAll();
}

void HotkeysMainWindow::setHotkeysLayout()
{
    // Current single selected item
    QTreeWidgetItem* item = entitiesTreeWidget->selectedItems().first();
    if (item == nullptr) return;

    // Skip if it's the top level section item
    for (int i = 0; i < entitiesTreeWidget->topLevelItemCount(); ++i)
    {
        if (item == entitiesTreeWidget->topLevelItem(i)) return;
    }


    const QPair<QString, QString> specialItemInfo = item->data(0, Qt::UserRole).value<QPair<QString, QString>>();

    const QString& factionShortName = specialItemInfo.first;
    const QString& entityName = specialItemInfo.second;

    QVBoxLayout* hotkeysLayout = new QVBoxLayout;

    for (const auto & faction : factions)
    {
        if (faction.getShortName() != factionShortName) continue;

        for (const auto & currentTypeEntities : faction.getEntitiesMap())
        {
            for (const auto & entity : currentTypeEntities)
            {
                if (entity.getName() != entityName) continue;

                for (const auto & action : entity.getActions())
                {
                    ActionHotkeyWidget* actionHotkey = new ActionHotkeyWidget(CSFPARSER->GetStringValue(action.getCsfString()),
                                                                              QChar{static_cast<char16_t>(CSFPARSER->GetHotkey(action.getCsfString()))},
                                                                              action.getName());
                    hotkeysLayout->addWidget(actionHotkey);
                }
            }
        }
    }
    // Condense the actions at the top
    hotkeysLayout->addStretch(1);

    if (hotkeysScrollWidget != nullptr) hotkeysScrollWidget->deleteLater();
    hotkeysScrollWidget = new QWidget;
    hotkeysScrollWidget->setLayout(hotkeysLayout);
    hotkeysScrollWidget->setMinimumSize(hotkeysScrollWidget->sizeHint());

    hotkeysArea->setWidget(hotkeysScrollWidget);
}

void HotkeysMainWindow::onAbout()
{
    // if dialog already exists
    if (aboutDialog != nullptr)
    {
        aboutDialog->activateWindow();
        return;
    }

    QVBoxLayout* authorsL = new QVBoxLayout;
    authorsL->addWidget(new QLabel{tr("Authors: ") + AUTHORS});

    QGridLayout* contentL = new QGridLayout;
    contentL->addLayout(authorsL, 0, 0);
    QLabel* pixmap = new QLabel;
    pixmap->setPixmap(QPixmap::fromImage(GUIConfig::decodeDefaultWebpIcon()));
    contentL->addWidget(pixmap, 0, 1);
    QLabel* textL = new QLabel{tr("Program licensed by GNU GPL v3")};
    textL->setWordWrap(true);
    textL->setAlignment(Qt::AlignJustify);
    contentL->addWidget(textL, 1, 0);
    contentL->setSizeConstraint(QLayout::SetFixedSize);

    aboutDialog = new QDialog{this};
    aboutDialog->setWindowTitle(tr("About"));
    aboutDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    aboutDialog->setWindowFlags(aboutDialog->windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);

    connect(aboutDialog, &QDialog::finished, this, [this]()
    {
        aboutDialog->deleteLater();
        aboutDialog = nullptr;
    });

    QDialogButtonBox* buttons = new QDialogButtonBox{QDialogButtonBox::Ok,
                                                     Qt::Orientation::Horizontal,
                                                     aboutDialog};

    connect(buttons, &QDialogButtonBox::accepted, aboutDialog, &QDialog::accept);

    QHBoxLayout* buttonsL = new QHBoxLayout;
    buttonsL->addStretch();
    buttons->button(QDialogButtonBox::Ok)->setFixedWidth(100);
    buttonsL->addWidget(buttons->button(QDialogButtonBox::Ok));
    buttonsL->addStretch();
    buttonsL->setAlignment(Qt::AlignCenter);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(contentL);
    mainL->addLayout(buttonsL);

    aboutDialog->setLayout(mainL);
    aboutDialog->show();
    aboutDialog->raise();
    aboutDialog->activateWindow();
}
