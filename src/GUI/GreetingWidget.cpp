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
#include "GreetingWidget.hpp"

GreetingWidget::GreetingWidget(QWidget* parent) : QWidget(parent)
{
    QPushButton* btnNewProject  = nullptr;
    QPushButton* btnLoadProject = nullptr;
    QHBoxLayout* ltButtons      = nullptr;
    QVBoxLayout* ltMain         = nullptr;
    QHBoxLayout* ltSettings     = nullptr;
    QLabel*      lblLanguage    = nullptr;
    QComboBox*   cmbLangList    = nullptr;
    QVBoxLayout* ltLanguages    = nullptr;

    // Add "New Project" and "Load Project" buttons to the window
    btnNewProject = new QPushButton(tr("NEW") + '\n' + tr("PROJECT"));
    btnNewProject->setFixedSize(PROGRAM_CONSTANTS->START_BUTTON_SIZE);
    btnNewProject->setObjectName(nameof(btnNewProject));
    connect(btnNewProject, &QPushButton::clicked, this, [this](bool)
    {
        emit pressed(GreetingWidget::StandartButtons::NewProject);
    });

    btnLoadProject = new QPushButton(tr("LOAD") + '\n' + tr("PROJECT"));
    btnLoadProject->setFixedSize(PROGRAM_CONSTANTS->START_BUTTON_SIZE);
    btnLoadProject->setObjectName(nameof(btnLoadProject));
    connect(btnLoadProject, &QPushButton::clicked, this, [this](bool)
    {
        emit pressed(GreetingWidget::StandartButtons::LoadProject);
    });

    lblLanguage = new QLabel(tr("LANGUAGE"));
    lblLanguage->setObjectName(nameof(lblLanguage));

    cmbLangList = new QComboBox();
    cmbLangList->setObjectName(nameof(cmbLangList));
    for (int i = 0; i < static_cast<int>(Languages::Count); ++i)
        cmbLangList->addItem(Unsorted::GetLanguageFullName(static_cast<Languages>(i)));
    cmbLangList->setCurrentIndex(static_cast<int>(WINDOW_MANAGER->GetLanguage()));
    cmbLangList->setCurrentText(PROGRAM_CONSTANTS->LANGUAGES_STRINGS.value(WINDOW_MANAGER->GetLanguage()).second);
    connect(cmbLangList, QOverload<int>::of(&QComboBox::activated), this, &GreetingWidget::languageChanged);
    
    QPushButton* btnSettings = new QPushButton();
    QPixmap      pxmSettings = QPixmap{PROGRAM_CONSTANTS->GEARS_ICON_FILE};
    btnSettings->setObjectName(nameof(btnSettings));
    btnSettings->setIcon(pxmSettings);
    btnSettings->setIconSize(pxmSettings.size());
    btnSettings->setFixedSize(pxmSettings.size());
    connect(btnSettings, &QPushButton::clicked, this, &GreetingWidget::btnSettings_Clicked);

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
    ltButtons->addWidget(btnNewProject);
    ltButtons->addWidget(btnLoadProject);
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
int GreetingWidget::GetGreetingTextAverageSize(const QString& text) const
{
    QLabel lblSizeCounting(text);
    lblSizeCounting.setWordWrap(true);
    return (int)((lblSizeCounting.sizeHint().height() + lblSizeCounting.sizeHint().width()) / 2.);
}
