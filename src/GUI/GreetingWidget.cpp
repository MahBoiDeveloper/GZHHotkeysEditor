#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "../Logger.hpp"
#include "GUIConfig.hpp"
#include "GreetingWidget.hpp"

GreetingWidget::GreetingWidget(Config::Languages language, QWidget* parent) : QWidget(parent)
{
    QLabel*      lblGreeting    = nullptr;
    QPushButton* btnNewProject  = nullptr;
    QPushButton* btnLoadProject = nullptr;
    QVBoxLayout* ltButtons      = nullptr;
    QHBoxLayout* ltContent      = nullptr;
    QLabel*      lblLanguage    = nullptr;
    QComboBox*   cmbLangList    = nullptr;
    QHBoxLayout* ltLanguages    = nullptr;
    QVBoxLayout* ltMain         = nullptr;

    // Makes greeting window unresizeable
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Program description
    lblGreeting = new QLabel(tr("Greetings, %username%. "
                                "You have launched the hotkey editing program "
                                "for the game Command and Conquer: Generals "
                                "and Command and Conquer: Generals — Zero Hour. "
                                "At the moment, the program supports in test mode "
                                "only the creation of hotkey maps based on pre-prepared hotkeys. "
                                "We hope that you will like the program."));
    lblGreeting->setWordWrap(true);
    lblGreeting->setAlignment(Qt::AlignmentFlag::AlignJustify);
    lblGreeting->setFixedWidth(GetGreetingTextAverageSize(lblGreeting->text()) + 50);

    // Add "New Project" and "Load Project" buttons to the window
    btnNewProject = new QPushButton(tr("New Project"));
    btnNewProject->setFixedSize(GUIConfig::startButtonsSize);
    connect(btnNewProject, &QPushButton::clicked, this, [=](bool)
    {
        emit pressed(GreetingWidget::StandartButtons::NewProject);
    });

    btnLoadProject = new QPushButton(tr("Load Project"));
    btnLoadProject->setFixedSize(GUIConfig::startButtonsSize);
    connect(btnLoadProject, &QPushButton::clicked, this, [=](bool)
    {
        emit pressed(GreetingWidget::StandartButtons::LoadProject);
    });

    ltButtons = new QVBoxLayout();
    ltButtons->setSpacing(50);
    ltButtons->setAlignment(Qt::AlignTop);
    ltButtons->addWidget(btnNewProject);
    ltButtons->addWidget(btnLoadProject);

    ltContent = new QHBoxLayout();
    ltContent->setAlignment(Qt::AlignLeft);
    ltContent->addLayout(ltButtons);
    ltContent->addWidget(lblGreeting);
    ltContent->setAlignment(lblGreeting, Qt::AlignTop);

    lblLanguage = new QLabel(tr("Language"));

    cmbLangList = new QComboBox();
    for (int i = 0; i < static_cast<int>(Config::Languages::Count); ++i)
        cmbLangList->addItem(Config::GetStringFromLangEnum(static_cast<Config::Languages>(i)));
    cmbLangList->setCurrentIndex(static_cast<int>(language));
    connect(cmbLangList, QOverload<int>::of(&QComboBox::activated), this, &GreetingWidget::languageChanged);
    
    ltLanguages = new QHBoxLayout();
    ltLanguages->addStretch(1);
    ltLanguages->setSpacing(10);
    ltLanguages->addWidget(lblLanguage);
    ltLanguages->addWidget(cmbLangList);

    ltMain = new QVBoxLayout();
    ltMain->setSpacing(50);
    ltMain->setContentsMargins(50, 50, 50, 30);
    ltMain->addLayout(ltContent);
    ltMain->addSpacing(80);
    ltMain->addLayout(ltLanguages);

    setLayout(ltMain);
}

/// @brief Calculate size of long description text block.
int GreetingWidget::GetGreetingTextAverageSize(const QString& text) const
{
    QLabel lblSizeCounting(text);
    lblSizeCounting.setWordWrap(true);
    return (int)((lblSizeCounting.sizeHint().height() + lblSizeCounting.sizeHint().width()) / 2.);
}
