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

    bg = new QButtonGroup;

    auto btnNewProject  = CreateButton(tr("New project"));
    bg->addButton(btnNewProject);

    auto btnLoadProject = CreateButton(tr("Load project"));
    btnLoadProject->setDisabled(true);
    bg->addButton(btnLoadProject);

    // Event OnClick()
    connect(bg, QOverload<int>::of(&QButtonGroup::idClicked), this,
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
    languageL->addSpacing(5);
    languageL->addWidget(langBox);
    languageL->setAlignment(Qt::AlignRight);

    // Main layout config
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
