#include "hotkeys_main_window.hpp"
#include "hotkey_element.hpp"
#include "listWidget/list_widget_building_item.hpp"

#include <Info.hpp>
#include <TechTreeJsonParser.hpp>
#include <gui_config.hpp>

#include <QMenuBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QScrollArea>
#include <QDebug>

HotkeysMainWindow::HotkeysMainWindow(const QVariant& configuration, QWidget* parent)
    : QMainWindow(parent)
    , factionsButtonsGroup{new QButtonGroup}
    , factionsTabs{new QTabWidget}
{
    resize(1200, 800);

    _configureMenu();

    connect(factionsButtonsGroup, &QButtonGroup::idClicked, this, &HotkeysMainWindow::setCurrentTab);

    factionsTabs->tabBar()->hide();

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(_createFactionsButtonsLayout());
    mainL->addWidget(factionsTabs);

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);
}

void HotkeysMainWindow::_configureMenu()
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

QLayout* HotkeysMainWindow::_createFactionsButtonsLayout() const
{
    std::vector<TechTreeJsonParser::FactionInfo> factions = TechTreeJsonParser::GetFactionsInfo();

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
                QWidget* newTab = new QWidget;
                newTab->setLayout(_createTabContent(QString::fromStdString(factions[sectionIndex + i].ShortName)));
                factionsTabs->addTab(newTab, "");

                QPushButton* factionButton = new QPushButton(QString::fromStdString(factions.at(sectionIndex + i).DisplayName));
                factionsButtonsGroup->addButton(factionButton);

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

    return factionsL;
}

QListWidget* HotkeysMainWindow::_createBuildingsList(const QString& factionName) const
{
    QVector<Building> buildings;
    for (int i = 0; i < 10; ++i)
    {
        buildings.append(Building{"PRCBunker", ""});
    }

    QListWidget* buildingsList = new QListWidget;

    int buildingIconMinimumHeight = 80;

    // smooth scrolling
    buildingsList->setVerticalScrollMode(QListWidget::ScrollMode::ScrollPerPixel);
    // icon size
    buildingsList->setIconSize(QSize{buildingIconMinimumHeight, buildingIconMinimumHeight});
    buildingsList->setSpacing(buildingIconMinimumHeight * 0.1);

    for (const auto & building : buildings)
    {
        buildingsList->addItem(new ListWidgetBuildingItem{building});
        buildingsList->item(buildingsList->count() - 1)->setText(QString{"%1 building %2"}.
                                                                 arg(factionName).
                                                                 arg(buildingsList->count()));
    }

    return buildingsList;
}

QLayout* HotkeysMainWindow::_createHotkeysLayout() const
{
    QVBoxLayout* hotkeysL = new QVBoxLayout;
    for(int i = 0; i < 5; ++i)
    {
        Qt::Key key = (Qt::Key)(Qt::Key::Key_A + i);

        QString hotkey = QKeySequence{key}.toString();

        HotkeyElement* hotkeyElement = new HotkeyElement(QString("action_%1").arg(i+1),
                                                         hotkey,
                                                         QString("GLAScudStormLaunch"));
        hotkeysL->addWidget(hotkeyElement);
    }

    return hotkeysL;
}

QLayout* HotkeysMainWindow::_createTabContent(const QString& factionName) const
{
    QWidget* scrollWidget = new QWidget;
    scrollWidget->setLayout(_createHotkeysLayout());
    // Get rid of element compression
    scrollWidget->setMinimumSize(scrollWidget->sizeHint());

    QScrollArea* hotkeysArea = new QScrollArea;
    hotkeysArea->setWidget(scrollWidget);

    // Fill all available space
    hotkeysArea->setWidgetResizable(true);

    QVBoxLayout* buildingConfigurationL = new QVBoxLayout;
    buildingConfigurationL->addWidget(hotkeysArea);
    buildingConfigurationL->addWidget(new QScrollArea);

    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->addWidget(_createBuildingsList(factionName));
    contentL->addLayout(buildingConfigurationL);

    // building list's configuration stretch power
    contentL->setStretch(0,1);
    contentL->setStretch(1,3);

    return contentL;
}

void HotkeysMainWindow::setCurrentTab(int negativeId)
{
    // invert index
    int normalIndex = (negativeId + 2) * (-1);

    factionsTabs->setCurrentIndex(normalIndex);
}

void HotkeysMainWindow::onAbout()
{
    // not
    if (aboutDialog != nullptr)
    {
        aboutDialog->activateWindow();
        return;
    }

    QVBoxLayout* authorsL = new QVBoxLayout;
    authorsL->addWidget(new QLabel(tr("Authors: ") + AUTHORS));

    QGridLayout* contentL = new QGridLayout;
    contentL->addLayout(authorsL, 0, 0);
    QLabel* pixmap = new QLabel;
    pixmap->setPixmap(QPixmap::fromImage(GuiConfig::decodeWebpIcon(GuiConfig::standartSmallImageName)));
    contentL->addWidget(pixmap, 0, 1);
    QLabel* textL = new QLabel(tr("Program licensed by GNU GPL v3"));
    textL->setWordWrap(true);
    textL->setAlignment(Qt::AlignJustify);
    contentL->addWidget(textL, 1, 0);
    contentL->setSizeConstraint(QLayout::SetFixedSize);

    aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle(tr("About"));
    aboutDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    aboutDialog->setWindowFlags(aboutDialog->windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);
    connect(aboutDialog, &QDialog::finished, this, [this](){aboutDialog->deleteLater(); aboutDialog = nullptr;});

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok,
                                                     Qt::Orientation::Horizontal,
                                                     aboutDialog);
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
