#include <QDebug>
#include <QMenuBar>
#include <QDialog>
#include <QDialogButtonBox>
#include <QListView>
#include <QStringListModel>
#include <QScrollArea>

#include "../../Info.hpp"
#include "../../parsers/TechTreeJsonParser.hpp"

#include "../config.hpp"
#include "hotkeys_main_window.hpp"
#include "hotkey_element.hpp"

HotkeysMainWindow::HotkeysMainWindow(const QVariant& configuration, QWidget* parent) : QMainWindow(parent)
{
    resize(1200, 800);

    // configuring menu
    QMenu* fm = new QMenu(tr("File"));
    fm->addAction(tr("Special"));
    menuBar()->addMenu(fm);
    menuBar()->addAction(tr("View"));
    QMenu* settingsM = new QMenu(tr("Settings"));
    menuBar()->addMenu(settingsM);
    QAction* aboutA = new QAction(tr("About"));
    connect(aboutA, &QAction::triggered, this, &HotkeysMainWindow::onAbout);
    settingsM->addAction(aboutA);

    // configuring fractions layouts
    auto factions = TechTreeJsonParser::GetFactionsInfo();
    QBoxLayout* factionsL = nullptr;
    const int standartFactionsCount = 12;
    int factonsCount = factions.size();

    if (factonsCount == standartFactionsCount)
    {
        factionsL = new QHBoxLayout;

        QVBoxLayout* USA_L = new QVBoxLayout;
        USA_L->addWidget(new QPushButton(QString::fromStdString(factions.at(0).DisplayName)));

        QHBoxLayout* USA_powersL = new QHBoxLayout;
        USA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(1).DisplayName)));
        USA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(2).DisplayName)));
        USA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(3).DisplayName)));
        USA_L->addLayout(USA_powersL);

        QVBoxLayout* CHINA_L = new QVBoxLayout;
        CHINA_L->addWidget(new QPushButton(QString::fromStdString(factions.at(4).DisplayName)));

        QHBoxLayout* CHINA_powersL = new QHBoxLayout;
        CHINA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(5).DisplayName)));
        CHINA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(6).DisplayName)));
        CHINA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(7).DisplayName)));
        CHINA_L->addLayout(CHINA_powersL);

        QVBoxLayout* GLA_L = new QVBoxLayout;
        GLA_L->addWidget(new QPushButton(QString::fromStdString(factions.at(8).DisplayName)));

        QHBoxLayout* GLA_powersL = new QHBoxLayout;
        GLA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(9).DisplayName)));
        GLA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(10).DisplayName)));
        GLA_powersL->addWidget(new QPushButton(QString::fromStdString(factions.at(11).DisplayName)));
        GLA_L->addLayout(GLA_powersL);

        // Write information to the header layout
        factionsL->addLayout(USA_L);
        factionsL->addLayout(CHINA_L);
        factionsL->addLayout(GLA_L);
    }
    else
    {
        QHBoxLayout* firstL = new QHBoxLayout;
        QHBoxLayout* secondL = new QHBoxLayout;

        int i = 0;
        for (const auto & faction : factions)
        {
            if (i < factonsCount / 2)
            {
                firstL->addWidget(new QPushButton(QString::fromStdString(factions.at(i).DisplayName)));
            }
            else
            {
                secondL->addWidget(new QPushButton(QString::fromStdString(factions.at(i).DisplayName)));
            }
            ++i;
        }

        factionsL = new QVBoxLayout;
        factionsL->addLayout(firstL);
        factionsL->addLayout(secondL);
    }

    // buildings view list
    QStringListModel* buildingsModel = new QStringListModel;
    QStringList list;
    for (int i = 0; i < 10; ++i)
    {
        list << QString("Building %1").arg(i+1);
    }
    buildingsModel->setStringList(list);

    QListView* buildings = new QListView;
    buildings->setModel(buildingsModel);

    QVBoxLayout* hotkeysL1 = new QVBoxLayout;
    QVBoxLayout* hotkeysL2 = new QVBoxLayout;
    QVBoxLayout* hotkeysL3 = new QVBoxLayout;
    for(int i = 0; i < 3; ++i)
    {
        hotkeysL1->addWidget(new HotkeyElement(QString("action_%1").arg(i+1),
                                               QString("hotkey_%1").arg(i+1),
                                               QString("sources/icons/Gen1_Hacker_Icons.webp")));
        hotkeysL2->addWidget(new HotkeyElement(QString("action_%1").arg(i+1),
                                               QString("hotkey_%1").arg(i+1),
                                               QString("sources/icons/Gen1_Hacker_Icons.webp")));
        hotkeysL3->addWidget(new HotkeyElement(QString("action_%1").arg(i+1),
                                               QString("hotkey_%1").arg(i+1),
                                               QString("sources/icons/Gen1_Hacker_Icons.webp")));
    }
    QScrollArea* arr1 = new QScrollArea;
    QScrollArea* arr2 = new QScrollArea;
    QScrollArea* arr3 = new QScrollArea;
    arr1->setLayout(hotkeysL1);
//    arr2->setLayout(hotkeysL2);
//    arr3->setLayout(hotkeysL3);
    arr1->setWidgetResizable(true);
    arr2->setWidgetResizable(true);
    arr3->setWidgetResizable(true);

    QVBoxLayout* buildingConfigurationL = new QVBoxLayout;
    buildingConfigurationL->addWidget(arr1);
    buildingConfigurationL->addWidget(arr2);
    buildingConfigurationL->addWidget(arr3);

    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->addWidget(buildings);
    contentL->addLayout(buildingConfigurationL);
    // building list an configuration stretch power
    contentL->setStretch(0,1);
    contentL->setStretch(1,3);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(factionsL);
    mainL->addLayout(contentL);

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);
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
    pixmap->setPixmap(QPixmap::fromImage(Config::decodeWebpIcon("NoImageSmall")));
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