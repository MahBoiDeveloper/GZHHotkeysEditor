#include <QDebug>
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>
#include <QScrollArea>

#include "editor.hpp"
#include "hotkeyelement.hpp"

Editor::Editor(Registry::Games game, bool saveToGame, QWidget *parent) : QMainWindow(parent)
{
    // configuring menu
    QMenu* fm = new QMenu(tr("File"));
    fm->addAction(tr("Special"));
    menuBar()->addMenu(fm);
    menuBar()->addAction(tr("View"));
    QMenu* settingsM = new QMenu(tr("Settings"));
    menuBar()->addMenu(settingsM);

    QVBoxLayout* mainL = new QVBoxLayout;
//    for(int i = 0; i < 7; i++)
//        mainL->addWidget(new HotkeyElement(QString("action_%1").arg(i+1),
//                                           QString("hotkey_%1").arg(i+1),
//                                           QString("sources/icons/Gen1_Hacker_Icons.webp")));
//    hotkeysWidget->setLayout(mainL);
    QVBoxLayout* USA_L = new QVBoxLayout;
    USA_L->addWidget(new QPushButton("USA"));
    QHBoxLayout* USA_fractionsL = new QHBoxLayout;
    USA_L->addWidget(new QPushButton("AIR"));
    USA_L->addWidget(new QPushButton("LASER"));
    USA_L->addWidget(new QPushButton("USA"));

//    fractionsL->addWidget(new QPushButton("CHINA"));
//    fractionsL->addWidget(new QPushButton("GLA"));

    QHBoxLayout* fractionsL = new QHBoxLayout;

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);
}
