#include <QButtonGroup>
#include <QLayout>
#include <QResizeEvent>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QComboBox>
#include <QLabel>

#include "startwidget.hpp"

QPushButton* StartWidget::CreateButton(const QString& qstrButtonName) const
{
    QPushButton* btnSample = new QPushButton(qstrButtonName);
    btnSample->setMinimumSize(100, 15);

    return btnSample;
}

StartWidget::StartWidget(Config::Languages language, QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainButtons = new QButtonGroup;

    auto btnNewProject  = CreateButton(tr("New project"));
    mainButtons->addButton(btnNewProject);

    auto btnLoadProject = CreateButton(tr("Load project"));
    btnLoadProject->setDisabled(true);
    mainButtons->addButton(btnLoadProject);

    for(auto & button : mainButtons->buttons())
    {
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        button->setFixedSize(QSize(Config::startButtonsMinWidth, button->sizeHint().height()));
    }

    // Event OnClick()
    connect(mainButtons, QOverload<int>::of(&QButtonGroup::idClicked), this,
        [=](int id)
        {
            int index = (-1)*id - 2; // QButtonGroup assign index -2 to first button
            emit StartWidget::pressed(index);
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
    languageL->addWidget(languageName);
//    languageL->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    languageL->addSpacing(5);
    languageL->addWidget(langBox);
    languageL->setAlignment(Qt::AlignRight);

    // Description config
    QLabel* greeting = new QLabel(tr("Greetings, my friend."));
    greeting->setWordWrap(true);

    // Main layout config
    QGridLayout* mainL = new QGridLayout;
    mainL->setSpacing(50);
    mainL->setContentsMargins(50, 10, 50, 10);
    mainL->setAlignment(Qt::AlignCenter);
    mainL->addWidget(mainButtons->buttons().at(0), 0, 0, Qt::AlignLeft);
    mainL->addWidget(mainButtons->buttons().at(1), 1, 0, Qt::AlignLeft);
    mainL->addWidget(greeting, 0, 1);
    mainL->addLayout(languageL, 3, 1, Qt::AlignRight);
    setLayout(mainL);
}

StartWidget::~StartWidget()
{
    delete mainButtons;
}
