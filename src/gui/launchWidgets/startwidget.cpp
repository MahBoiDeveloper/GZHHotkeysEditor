#include <QButtonGroup>
#include <QLayout>
#include <QResizeEvent>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QDesktopWidget>

#include "startwidget.hpp"

QPushButton* StartWidget::CreateButton(const QString& qstrButtonName) const
{
    QPushButton* btnSample = new QPushButton(qstrButtonName);
    btnSample->setMinimumSize(100, 15);

    return btnSample;
}

StartWidget::StartWidget(Config::Languages language, QWidget *parent) : QWidget(parent)
{
//    qDebug() << QApplication::desktop()->screenGeometry(this).size() * Config::recomendedStartWidgetSizeRatio;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto btnNewProject  = CreateButton(tr("New project"));
    mainButtons.addButton(btnNewProject);

    auto btnLoadProject = CreateButton(tr("Load project"));
    btnLoadProject->setDisabled(true);  // temporary
    mainButtons.addButton(btnLoadProject);

    for(auto & button : mainButtons.buttons())
        button->setFixedSize(Config::startButtonsSize);

    // Event OnClick()
    connect(&mainButtons, QOverload<int>::of(&QButtonGroup::idClicked), this,
        [=](int id)
        {
            int index = (-1)*id - 2; // QButtonGroup assign index -2 to first button
            emit StartWidget::pressed(static_cast<Buttons>(index));
        }
    );

    // Languages config
    QComboBox* langBox = new QComboBox;
    for (int i = 0; i < static_cast<int>(Config::Languages::Count); ++i)
    {
        langBox->addItem(Config::GetStringFromLangEnum(static_cast<Config::Languages>(i)));
    }
    langBox->setCurrentIndex(static_cast<int>(language));
    connect(langBox, QOverload<int>::of(&QComboBox::activated), this, &StartWidget::languageChanged);
    QLabel*      languageName = new QLabel(tr("Language"));
    QHBoxLayout* languageL    = new QHBoxLayout;
    languageL->addStretch(1);
    languageL->setSpacing(10);
    languageL->addWidget(languageName);
    languageL->addWidget(langBox);

    // Description config
    QLabel* greeting = new QLabel(tr("Greetings, my friend. There is an amazing super cool program "
                                     "for editing hotkeys."));
    greeting->setWordWrap(true);
    int averageSize = (int)((greeting->sizeHint().height() + greeting->sizeHint().width()) / 2.);
    greeting->setFixedWidth(averageSize);
    greeting->setAlignment(Qt::AlignJustify);

    // Main layout config
    QGridLayout* mainL = new QGridLayout;
    mainL->setSpacing(50);
    mainL->setContentsMargins(30, 50, 50, 20);
    mainL->addWidget(mainButtons.buttons().at(0), 0, 0, Qt::AlignLeft | Qt::AlignTop);
    mainL->addWidget(mainButtons.buttons().at(1), 1, 0, Qt::AlignLeft | Qt::AlignTop);
    mainL->addWidget(greeting, 0, 1, Qt::AlignTop);
    mainL->addItem(new QSpacerItem(0, 100, QSizePolicy::Fixed, QSizePolicy::Fixed), 2, 0);
    mainL->addLayout(languageL, 3, 1);
    setLayout(mainL);
}
