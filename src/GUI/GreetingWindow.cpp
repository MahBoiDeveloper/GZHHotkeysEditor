#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "../Logger.hpp"
#include "../NameOfExt.hpp"
#include "../ProgramConstants.hpp"
#include "../Unsorted.hpp"
#include "WindowManager.hpp"
#include "ImageManager.hpp"
#include "GreetingWindow.hpp"

GreetingWindow::GreetingWindow(QWidget* parent) : QWidget(parent)
{
    QPushButton* btnLoadFromGame = nullptr;
    QPushButton* btnLoadFromFile = nullptr;
    QHBoxLayout* ltButtons       = nullptr;
    QVBoxLayout* ltMain          = nullptr;
    QHBoxLayout* ltSettings      = nullptr;
    QLabel*      lblLanguage     = nullptr;
    QComboBox*   cmbLangList     = nullptr;
    QVBoxLayout* ltLanguages     = nullptr;

    // Add "New Project" and "Load Project" buttons to the window
    btnLoadFromGame = new QPushButton(tr("LOAD FROM") + '\n' + tr("THE GAME"));
    btnLoadFromGame->setFixedSize(PROGRAM_CONSTANTS->START_BUTTON_SIZE);
    btnLoadFromGame->setObjectName(nameof(btnLoadFromGame));
    connect(btnLoadFromGame, &QPushButton::clicked, this, &GreetingWindow::btnLoadFromGame_Clicked);

    btnLoadFromFile = new QPushButton(tr("LOAD FROM") + '\n' + tr("THE FILE"));
    btnLoadFromFile->setFixedSize(PROGRAM_CONSTANTS->START_BUTTON_SIZE);
    btnLoadFromFile->setObjectName(nameof(btnLoadFromFile));
    connect(btnLoadFromFile, &QPushButton::clicked, this, &GreetingWindow::btnLoadFromFile_Clicked);

    lblLanguage = new QLabel(tr("LANGUAGE"));
    lblLanguage->setObjectName(nameof(lblLanguage));

    cmbLangList = new QComboBox();
    cmbLangList->setObjectName(nameof(cmbLangList));
    for (int i = 0; i < static_cast<int>(Languages::Count); ++i)
        cmbLangList->addItem(Unsorted::GetLanguageFullName(static_cast<Languages>(i)));
    cmbLangList->setCurrentIndex(static_cast<int>(WINDOW_MANAGER->GetLanguage()));
    cmbLangList->setCurrentText(PROGRAM_CONSTANTS->LANGUAGES_STRINGS.value(WINDOW_MANAGER->GetLanguage()).second);
    connect(cmbLangList, QOverload<int>::of(&QComboBox::activated), this, &GreetingWindow::languageChanged);
    
    QPushButton* btnSettings = new QPushButton();
    QPixmap      pxmSettings = QPixmap{PROGRAM_CONSTANTS->GEARS_ICON_FILE};
    btnSettings->setObjectName(nameof(btnSettings));
    btnSettings->setIcon(pxmSettings);
    btnSettings->setIconSize(pxmSettings.size());
    btnSettings->setFixedSize(pxmSettings.size());
    connect(btnSettings, &QPushButton::clicked, this, &GreetingWindow::btnSettings_Clicked);

    ltLanguages = new QVBoxLayout();
    ltLanguages->addStretch(1);
    ltLanguages->setSpacing(10);
    ltLanguages->addWidget(lblLanguage);
    ltLanguages->addWidget(cmbLangList);

    ltSettings = new QHBoxLayout();
    ltSettings->addLayout(ltLanguages);
    ltSettings->addWidget(btnSettings);

    ltButtons = new QHBoxLayout();
    ltButtons->setSpacing(50);
    ltButtons->setAlignment(Qt::AlignTop);
    ltButtons->addWidget(btnLoadFromGame);
    ltButtons->addWidget(btnLoadFromFile);
    ltButtons->setSpacing(30);

    ltMain = new QVBoxLayout();
    ltMain->setAlignment(Qt::AlignCenter);
    ltMain->addLayout(ltButtons);
    ltMain->addLayout(ltSettings);
    ltMain->setSpacing(20);
    ltMain->setContentsMargins(160, 120, 160, 120);
    
    setLayout(ltMain);
}

/// @brief Calculate size of long description text block.
int GreetingWindow::GetGreetingTextAverageSize(const QString& text) const
{
    QLabel lblSizeCounting(text);
    lblSizeCounting.setWordWrap(true);
    return (int)((lblSizeCounting.sizeHint().height() + lblSizeCounting.sizeHint().width()) / 2.);
}
