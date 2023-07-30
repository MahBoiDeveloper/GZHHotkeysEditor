#include <QDebug>
#include <QMenuBar>
#include <QDialog>
#include <QDialogButtonBox>

#include "editor.hpp"
#include "../../Info.hpp"
#include "../config.hpp"
#include "hotkeyelement.hpp"

Editor::Editor(QVariant configuration, QWidget *parent) : QMainWindow(parent)
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
    connect(aboutA, &QAction::triggered, this, &Editor::onAbout);
    menuBar()->addAction(aboutA);

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

    QHBoxLayout* fractionsL = new QHBoxLayout;

    // main widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainL);
    setCentralWidget(centralWidget);
}

void Editor::onAbout() const
{
    QVBoxLayout* authorsL = new QVBoxLayout;
    authorsL->addWidget(new QLabel(tr("Authors: ") + AUTHORS));

    QGridLayout* contentL = new QGridLayout;
    contentL->addLayout(authorsL, 0, 0);
    QLabel* pixmap = new QLabel;
    pixmap->setPixmap(QPixmap::fromImage(Config::decodeWebpIcon("default")));
    contentL->addWidget(pixmap, 0, 1);
    QLabel* textL = new QLabel(tr("Program licensed by GNU GPL v3"));
    textL->setWordWrap(true);
    contentL->addWidget(textL, 1, 0);
    contentL->setSizeConstraint(QLayout::SetFixedSize);

    QDialog aboutDialog;
    aboutDialog.setWindowTitle(tr("About"));
    aboutDialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    aboutDialog.setWindowFlags(aboutDialog.windowFlags() &
                               ~Qt::WindowContextHelpButtonHint |
                                Qt::MSWindowsFixedSizeDialogHint);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Orientation::Horizontal, &aboutDialog);
    connect(buttons, &QDialogButtonBox::accepted, &aboutDialog, &QDialog::accept);
    QHBoxLayout* buttonsL = new QHBoxLayout;
    buttonsL->addStretch();
    buttons->button(QDialogButtonBox::Ok)->setFixedWidth(100);
    buttonsL->addWidget(buttons->button(QDialogButtonBox::Ok));
    buttonsL->addStretch();
    buttonsL->setAlignment(Qt::AlignCenter);

    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->addLayout(contentL);
    mainL->addLayout(buttonsL);
    aboutDialog.setLayout(mainL);
    aboutDialog.exec();
    aboutDialog.raise();
    aboutDialog.activateWindow();
}
