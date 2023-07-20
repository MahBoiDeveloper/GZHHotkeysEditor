#include <QButtonGroup>
#include <QLayout>
#include <QResizeEvent>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QComboBox>
#include <QLabel>

#include "startwidget.hpp"

QPushButton* StartWidget::initButton(const QString& name) const
{
    QPushButton* button = new QPushButton(name);
    button->setMinimumHeight(height()/3);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // ------outdated-------
    // changing the button size relative to the window size
//    connect(this, &StartWidget::resized, button,
//        [button](int height){
//            button->setFixedHeight(button->getBaseHeight() + height/10);
//        }
//    );
    //----------------------
    return button;
}

// ------outdated-------
// when resized emit height
//void StartWidget::resizeEvent(QResizeEvent *event)
//{
//    QWidget::resizeEvent(event);
//    emit resized(event->size().height());
//}
//----------------------

StartWidget::StartWidget(Config::Languages language, QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    bg = new QButtonGroup;
    bg->addButton(initButton(tr("New project")));
    bg->addButton(initButton(tr("Load project")));
    connect(bg, QOverload<int>::of(&QButtonGroup::idClicked), this,
        [=](int id){
            int index = (-1)*id - 2; // QButtonGroup assign index -2 to first button
            emit StartWidget::pressed(index);
        }
    );

    // languages config
    QComboBox* langBox = new QComboBox;
    langBox->addItem("English");
    langBox->addItem("Русский");
    langBox->setCurrentIndex(static_cast<int>(language));
    connect(langBox, QOverload<int>::of(&QComboBox::activated), this, &StartWidget::languageChanged);
    QLabel* languageName = new QLabel(tr("Language"));
    QHBoxLayout* languageL = new QHBoxLayout;
    languageL->addWidget(languageName);
    languageL->addSpacing(5);
    languageL->addWidget(langBox);
    languageL->setAlignment(Qt::AlignRight);

    // main layout config
    QVBoxLayout* vl = new QVBoxLayout;
    vl->addStretch(5);
    vl->addWidget(bg->buttons().at(0));
    vl->addStretch(2);
    vl->addWidget(bg->buttons().at(1));
    vl->addStretch(5);
    vl->setContentsMargins(120, 10, 120, 30);
    vl->setAlignment(Qt::AlignCenter);
    vl->addLayout(languageL);
    setLayout(vl);
}

StartWidget::~StartWidget()
{
}
