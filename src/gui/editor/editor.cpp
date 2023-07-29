#include <QDebug>
#include <QMenuBar>
#include <QApplication>
#include <QTranslator>
#include <QScrollArea>
#include <QDialog>
#include <QFile>
#include <QDialogButtonBox>

#include "editor.hpp"
#include "../Info.hpp"
#include "../config.hpp"
#include "hotkeyelement.hpp"

#include "webp/decode.h"

Editor::Editor(Registry::Games game, bool saveToGame, QWidget *parent) : QMainWindow(parent)
{
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

QImage Editor::decodeWebpIcon(const QString &iconName)
{
    const QString iconPostfix   = ".webp";
    QFile iconFile(Config::iconsPath + "/" + iconName + iconPostfix);
    if(iconFile.open(QIODevice::ReadOnly))
    {
        QByteArray imageData = iconFile.readAll();
        iconFile.close();
        int width, height;
        uint8_t* decodedImage = WebPDecodeRGBA((const uint8_t*)imageData.constData(), imageData.size(), &width, &height);
        return QImage(decodedImage, width, height, QImage::Format_RGBA8888);
    }
    else
    {
        qDebug() << "File not opened!";
        return QImage();
    }
}

void Editor::onAbout() const
{
    QVBoxLayout* authorsL = new QVBoxLayout;
    authorsL->addWidget(new QLabel(tr("Authors: ") + AUTHORS));

    QGridLayout* mainL = new QGridLayout;
    mainL->addLayout(authorsL, 0, 0);
    QLabel* pixmap = new QLabel;
    pixmap->setPixmap(QPixmap::fromImage(decodeWebpIcon("default")));
    mainL->addWidget(pixmap, 0, 1);
    QLabel* textL = new QLabel(tr("Program licensed by GNU GPL v3"));
    textL->setWordWrap(true);
    mainL->addWidget(textL, 1, 0);
    mainL->setSizeConstraint(QLayout::SetFixedSize);

    QDialog aboutDialog;
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Orientation::Horizontal, &aboutDialog);
    connect(buttons, &QDialogButtonBox::accepted, &aboutDialog, &QDialog::accept);
    mainL->addWidget(buttons, 2, 1);
    aboutDialog.setWindowFlags(aboutDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    aboutDialog.setWindowTitle(tr("About"));
    aboutDialog.setLayout(mainL);
    aboutDialog.exec();
}
