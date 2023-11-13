#include <QButtonGroup>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QDesktopWidget>

#include "greeting_widget.hpp"

QPushButton* GreetingWidget::CreateButton(const QString& qstrButtonName) const
{
    QPushButton* btnSample = new QPushButton(qstrButtonName);
    btnSample->setMinimumSize(100, 15);

    return btnSample;
}

GreetingWidget::GreetingWidget(Config::Languages language, QWidget *parent) : QWidget(parent)
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
            emit GreetingWidget::pressed(static_cast<Buttons>(index));
        }
    );

    // Languages config
    QComboBox* langBox = new QComboBox;
    for (int i = 0; i < static_cast<int>(Config::Languages::Count); ++i)
    {
        langBox->addItem(Config::GetStringFromLangEnum(static_cast<Config::Languages>(i)));
    }
    langBox->setCurrentIndex(static_cast<int>(language));
    connect(langBox, QOverload<int>::of(&QComboBox::activated), this, &GreetingWidget::languageChanged);
    QLabel*      languageName = new QLabel(tr("Language"));
    QHBoxLayout* languageL    = new QHBoxLayout;
    languageL->addStretch(1);
    languageL->setSpacing(10);
    languageL->addWidget(languageName);
    languageL->addWidget(langBox);

    // Description config
    QLabel* greeting = new QLabel(tr("Greetings, %username%. "
                                     "You have launched the hotkey editing program "
                                     "for the game Command and Conquer: Generals "
                                     "and Command and Conquer: Generals — Zero Hour. "
                                     "At the moment, the program supports in test mode "
                                     "only the creation of hotkey maps based on pre-prepared hotkeys. "
                                     "We hope that you will like the program."));
    greeting->setWordWrap(true);
    greeting->setAlignment(Qt::AlignmentFlag::AlignJustify);

    // label for size counting
    QLabel labelForSize(greeting->text());
    labelForSize.setWordWrap(true);

    int averageSize = (int)((labelForSize.sizeHint().height() + labelForSize.sizeHint().width()) / 2.);
    greeting->setFixedWidth(averageSize + 50);

    // Main layout config
    QVBoxLayout* buttonsL = new QVBoxLayout;
    buttonsL->setSpacing(50);
    buttonsL->setAlignment(Qt::AlignLeft);
    buttonsL->addWidget(mainButtons.buttons().at(0));
    buttonsL->addWidget(mainButtons.buttons().at(1));
    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->setAlignment(Qt::AlignLeft);
    contentL->addLayout(buttonsL);
    contentL->addWidget(greeting);
    contentL->setAlignment(greeting, Qt::AlignTop);
    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->setSpacing(50);
    mainL->setContentsMargins(50, 50, 50, 30);
    mainL->addLayout(contentL);
    mainL->addLayout(languageL);
    setLayout(mainL);
}
