#include <QComboBox>
#include <QLabel>

#include "../../Logger.hpp"
#include "../gui_config.hpp"
#include "greeting_widget.hpp"

GreetingWidget::GreetingWidget(Config::Languages language, QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // add standart buttons to main buttons group
    addStandartButton(GreetingWidget::StandartButtons::NewProject, tr("New project"));
    addStandartButton(GreetingWidget::StandartButtons::LoadProject, tr("Load project"));
    mainButtons.button(-3)->setDisabled(true);  // TODO: temporary;

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
    greeting->setFixedWidth(getGreetingAverageSize(greeting->text()) + 50);

    QVBoxLayout* buttonsL = new QVBoxLayout;
    buttonsL->setSpacing(50);
    buttonsL->setAlignment(Qt::AlignTop);
    for (const auto& button : mainButtons.buttons())
    {
        buttonsL->addWidget(button);
    }

    QHBoxLayout* contentL = new QHBoxLayout;
    contentL->setAlignment(Qt::AlignLeft);
    contentL->addLayout(buttonsL);
    contentL->addWidget(greeting);
    contentL->setAlignment(greeting, Qt::AlignTop);

    // Main layout
    QVBoxLayout* mainL = new QVBoxLayout;
    mainL->setSpacing(50);
    mainL->setContentsMargins(50, 50, 50, 30);
    mainL->addLayout(contentL);
    mainL->addSpacing(80);
    // Languages choosing box
    mainL->addLayout(createLanguageLayout(language, tr("Language")));
    setLayout(mainL);
}

void GreetingWidget::addStandartButton(GreetingWidget::StandartButtons standartButton, const QString& buttonName)
{
    // creating standart button
    QPushButton* button = new QPushButton(buttonName);
//    button->setMinimumSize(100, 15);
    button->setFixedSize(GuiConfig::startButtonsSize);
    mainButtons.addButton(button);

    // Event OnClick()
    connect(button, &QPushButton::clicked, this, [=](bool)
        {
            emit pressed(standartButton);
        }
    );
}

QHBoxLayout *GreetingWidget::createLanguageLayout(Config::Languages language, const QString &labelText) const
{
    QComboBox* langBox = new QComboBox;
    // add languages labels
    for (int i = 0; i < static_cast<int>(Config::Languages::Count); ++i)
    {
        langBox->addItem(Config::GetStringFromLangEnum(static_cast<Config::Languages>(i)));
    }
    // set current language
    langBox->setCurrentIndex(static_cast<int>(language));
    connect(langBox, QOverload<int>::of(&QComboBox::activated), this, &GreetingWidget::languageChanged);
    // create layout
    QLabel* languageName = new QLabel(labelText);
    QHBoxLayout* languageL = new QHBoxLayout;
    languageL->addStretch(1);
    languageL->setSpacing(10);
    languageL->addWidget(languageName);
    languageL->addWidget(langBox);
    return languageL;
}

int GreetingWidget::getGreetingAverageSize(const QString &text) const
{
    // label for size calculation
    QLabel labelForSizeCounting(text);
    labelForSizeCounting.setWordWrap(true);
    // calculate size
    return (int)((labelForSizeCounting.sizeHint().height() + labelForSizeCounting.sizeHint().width()) / 2.);
}
