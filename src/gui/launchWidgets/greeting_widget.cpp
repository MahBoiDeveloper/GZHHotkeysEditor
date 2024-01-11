#include "../../Logger.hpp"
#include "../gui_config.hpp"
#include "greeting_widget.hpp"

GreetingWidget::GreetingWidget(Config::Languages language, QWidget* parent) : QWidget(parent)
{
    // Makes greeting window unresizeable
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Program description
    lblGreeting = std::make_unique<QLabel>(tr("Greetings, %username%. "
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
    btnNewProject = std::make_unique<QPushButton>(tr("New Project"));
    btnNewProject->setFixedSize(GuiConfig::startButtonsSize);
    connect(btnNewProject.get(), &QPushButton::clicked, this, [=](bool)
    {
        emit pressed(GreetingWidget::StandartButtons::NewProject);
    });

    btnLoadProject = std::make_unique<QPushButton>(tr("Load Project"));
    btnLoadProject->setFixedSize(GuiConfig::startButtonsSize);
    connect(btnLoadProject.get(), &QPushButton::clicked, this, [=](bool)
    {
        emit pressed(GreetingWidget::StandartButtons::LoadProject);
    });

    ltButtons = std::make_unique<QVBoxLayout>();
    ltButtons->setSpacing(50);
    ltButtons->setAlignment(Qt::AlignTop);
    ltButtons->addWidget(btnNewProject.get());
    ltButtons->addWidget(btnLoadProject.get());

    ltContent = std::make_unique<QHBoxLayout>();
    ltContent->setAlignment(Qt::AlignLeft);
    ltContent->addLayout(ltButtons.get());
    ltContent->addWidget(lblGreeting.get());
    ltContent->setAlignment(lblGreeting.get(), Qt::AlignTop);

    lblLanguage = std::make_unique<QLabel>(tr("Language"));

    cmbLangList = std::make_unique<QComboBox>();
    for (int i = 0; i < static_cast<int>(Config::Languages::Count); ++i)
        cmbLangList->addItem(Config::GetStringFromLangEnum(static_cast<Config::Languages>(i)));
    cmbLangList->setCurrentIndex(static_cast<int>(language));
    connect(cmbLangList.get(), QOverload<int>::of(&QComboBox::activated), this, &GreetingWidget::languageChanged);
    
    ltLanguages = std::make_unique<QHBoxLayout>();
    ltLanguages->addStretch(1);
    ltLanguages->setSpacing(10);
    ltLanguages->addWidget(lblLanguage.get());
    ltLanguages->addWidget(cmbLangList.get());

    ltMain = std::make_unique<QVBoxLayout>();
    ltMain->setSpacing(50);
    ltMain->setContentsMargins(50, 50, 50, 30);
    ltMain->addLayout(ltContent.get());
    ltMain->addSpacing(80);
    ltMain->addLayout(ltLanguages.get());

    setLayout(ltMain.get());
}

int GreetingWidget::GetGreetingTextAverageSize(const QString& text) const
{
    QLabel lblSizeCounting(text);
    lblSizeCounting.setWordWrap(true);
    return (int)((lblSizeCounting.sizeHint().height() + lblSizeCounting.sizeHint().width()) / 2.);
}
