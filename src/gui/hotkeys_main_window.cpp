#include "hotkeys_main_window.hpp"

#include <QMenuBar>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>

#include "hotkey_element.hpp"
#include "gui_config.hpp"
#include "../Logger.hpp"
#include "../Info.hpp"
#include "../Parsers/TechTreeJsonParser.hpp"

HotkeysMainWindow::HotkeysMainWindow(const QVariant& configuration, QWidget* parent)
    : QMainWindow(parent)
    , factions{TechTreeJsonParser::GetFactions()}
    , factionsButtonsGroup{new QButtonGroup{this}}
{
    resize(1200, 800);

    configureMenu();

    //============================ Entities Tree Widget configure =============================

    entitiesTreeWidget.header()->hide();
    // smooth scrolling
    entitiesTreeWidget.setVerticalScrollMode(QListWidget::ScrollMode::ScrollPerPixel);
    // icon size
    entitiesTreeWidget.setIconSize(QSize{GuiConfig::entityIconMinimumHeight, GuiConfig::entityIconMinimumHeight});
//    entitiesTreeWidget.setSpacing(GuiConfig::entityIconMinimumHeight * 0.1);

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

                QPushButton* factionButton = new QPushButton(currentFaction.getDisplayName());

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

    // TODO: temporary
    connect(&factionsButtonsGroup, &QButtonGroup::idClicked, this, [=](int factionButtonId)
    {
        setHotkeysLayout(factionsButtonsGroup.button(factionButtonId)->text());
    });

    //=========================================================================================

    // Fill all available space
    hotkeysArea.setWidgetResizable(true);

    QVBoxLayout* buildingConfigurationL = new QVBoxLayout;
    buildingConfigurationL->addWidget(&hotkeysArea);
    buildingConfigurationL->addWidget(new QScrollArea);

    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->addWidget(&entitiesTreeWidget);
    contentL->addLayout(buildingConfigurationL);

    // building list's configuration stretch power
    contentL->setStretch(0,1);
    contentL->setStretch(1,3);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(factionsL);
    mainL->addLayout(contentL);

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);

    // TODO: temporary
    factionsButtonsGroup.buttons().first()->click();
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
    entitiesTreeWidget.clear();

    for (auto it = Config::ENTITIES_STRINGS.cbegin(); it != Config::ENTITIES_STRINGS.cend(); ++it)
    {
        QTreeWidgetItem* newTopEntityItem = new QTreeWidgetItem;
        newTopEntityItem->setText(0, it.value());

        for (const auto & entity : TechTreeJsonParser::getFactionEntities(it.key(), factionShortName))
        {
            QTreeWidgetItem* currentNewEntityItem = new QTreeWidgetItem;
            currentNewEntityItem->setText(0, entity.getName());
            currentNewEntityItem->setIcon(0, QPixmap::fromImage(GuiConfig::decodeWebpIcon(entity.getName())));
            newTopEntityItem->addChild(currentNewEntityItem);
        }

        entitiesTreeWidget.addTopLevelItem(newTopEntityItem);
    }

    entitiesTreeWidget.expandAll();
}

void HotkeysMainWindow::setHotkeysLayout(const QString& factionShortName)
{
    QVBoxLayout* hotkeysLayout = new QVBoxLayout;

    for(int i = 0; i < 10; ++i)
    {
        Qt::Key key = (Qt::Key)(Qt::Key::Key_A + i);

        QString hotkey = QKeySequence{key}.toString();

        HotkeyElement* hotkeyElement = new HotkeyElement(QString("action_%1").arg(i+1), hotkey, QString(factionShortName));
        hotkeysLayout->addWidget(hotkeyElement);
    }

    hotkeysScrollWidgetPtr.reset(new QWidget);
    hotkeysScrollWidgetPtr->setLayout(hotkeysLayout);
    hotkeysScrollWidgetPtr->setMinimumSize(hotkeysScrollWidgetPtr->sizeHint());

    hotkeysArea.setWidget(hotkeysScrollWidgetPtr.get());
}

void HotkeysMainWindow::onAbout()
{
    // if dialog already exists
    if (aboutDialogPtr != nullptr)
    {
        aboutDialogPtr->activateWindow();
        return;
    }

    QVBoxLayout* authorsL = new QVBoxLayout;
    authorsL->addWidget(new QLabel(tr("Authors: ") + AUTHORS));

    QGridLayout* contentL = new QGridLayout;
    contentL->addLayout(authorsL, 0, 0);
    QLabel* pixmap = new QLabel;
    pixmap->setPixmap(QPixmap::fromImage(GuiConfig::decodeDefaultWebpIcon()));
    contentL->addWidget(pixmap, 0, 1);
    QLabel* textL = new QLabel(tr("Program licensed by GNU GPL v3"));
    textL->setWordWrap(true);
    textL->setAlignment(Qt::AlignJustify);
    contentL->addWidget(textL, 1, 0);
    contentL->setSizeConstraint(QLayout::SetFixedSize);

    aboutDialogPtr.reset(new QDialog(this));
    aboutDialogPtr->setWindowTitle(tr("About"));
    aboutDialogPtr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    aboutDialogPtr->setWindowFlags(aboutDialogPtr->windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);

    connect(aboutDialogPtr.get(), &QDialog::finished, this, [this]()
    {
        aboutDialogPtr.reset(nullptr);
    });

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok,
                                                     Qt::Orientation::Horizontal,
                                                     aboutDialogPtr.get());

    connect(buttons, &QDialogButtonBox::accepted, aboutDialogPtr.get(), &QDialog::accept);

    QHBoxLayout* buttonsL = new QHBoxLayout;
    buttonsL->addStretch();
    buttons->button(QDialogButtonBox::Ok)->setFixedWidth(100);
    buttonsL->addWidget(buttons->button(QDialogButtonBox::Ok));
    buttonsL->addStretch();
    buttonsL->setAlignment(Qt::AlignCenter);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(contentL);
    mainL->addLayout(buttonsL);

    aboutDialogPtr->setLayout(mainL);
    aboutDialogPtr->show();
    aboutDialogPtr->raise();
    aboutDialogPtr->activateWindow();
}
