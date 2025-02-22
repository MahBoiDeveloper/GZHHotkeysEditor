#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QLineEdit>
#include <QFontMetrics>

#include "../NameOfExt.hpp"
#include "LoadFromTheFileWindow.hpp"

LoadFromTheFileWindow::LoadFromTheFileWindow(QWidget* parent) : QDialog(parent)
{
    QHBoxLayout* ltOkAndCancel = new QHBoxLayout();
    QPushButton* btnOk         = new QPushButton(tr("START"));
    QPushButton* btnCancel     = new QPushButton(tr("BACK"));
    QHBoxLayout* ltBtnOk       = new QHBoxLayout();
    QHBoxLayout* ltBtnCancel   = new QHBoxLayout();
    btnOk->setObjectName(nameof(btnOk));
    btnOk->setFixedWidth(80);
    ltBtnOk->setAlignment(Qt::Alignment::enum_type::AlignRight);
    ltBtnOk->addWidget(btnOk);
    btnCancel->setObjectName(nameof(btnCancel));
    btnCancel->setFixedWidth(80);
    ltBtnCancel->setAlignment(Qt::Alignment::enum_type::AlignLeft);
    ltBtnCancel->addWidget(btnCancel);
    ltOkAndCancel->addLayout(ltBtnOk);
    ltOkAndCancel->addLayout(ltBtnCancel);
    connect(btnOk,     &QPushButton::clicked, this, [=, this] { emit btnStartClicked(); });
    connect(btnCancel, &QPushButton::clicked, this, [=, this] { emit btnBackClicked(); });

    // configure file path selection
    QLineEdit* pathToFileLineEdit = new QLineEdit();
    pathToFileLineEdit->setMaximumWidth(700);

    QFont font(pathToFileLineEdit->font());
    font.setPointSize(font.pointSize()-2); // reduce standart font size
    pathToFileLineEdit->setFont(font);

    QFileDialog* fileDialog = new QFileDialog(); // dialog for selecting the path to the file
    fileDialog->setFileMode(QFileDialog::FileMode::ExistingFile);
    fileDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    fileDialog->setNameFilters({tr("Text files") + "(*.txt)",
                                tr("Any files")  + "(*)"});
    connect(fileDialog, &QFileDialog::fileSelected, pathToFileLineEdit, &QLineEdit::setText);
    
    // review button
    QPushButton* btnReview = new QPushButton(tr("REVIEW"));
    btnReview->setObjectName(nameof(btnReview));
    btnReview->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnReview, &QPushButton::clicked, fileDialog, &QFileDialog::exec);

    // configure choise buttons
    QRadioButton* rdxLoadFromFile = new QRadioButton(tr("Load project"));
    rdxLoadFromFile->setChecked(true);
    rdxLoadFromFile->setObjectName(nameof(rdxLoadFromFile));
    connect(rdxLoadFromFile, &QPushButton::toggled, this, [=, this](bool checked)
    {
        pathToFileLineEdit->setEnabled(checked);
        btnReview->setEnabled(checked);
    });

    QRadioButton* rdxLoadFromGame = new QRadioButton(tr("Load installed game hotkey map"));
    rdxLoadFromGame->setObjectName(nameof(rdxLoadFromGame));

    QHBoxLayout* ltReview = new QHBoxLayout();
    ltReview->addWidget(pathToFileLineEdit);
    ltReview->addSpacing(5);
    ltReview->addWidget(btnReview);
    ltReview->setContentsMargins(rdxLoadFromFile->sizeHint().width() -
                                QFontMetrics(rdxLoadFromFile->font()).horizontalAdvance(rdxLoadFromFile->text()),
                                0,0,0);

    // configure dialog view
    QVBoxLayout* ltMainBlock = new QVBoxLayout();
    ltMainBlock->setContentsMargins(80,0,80,0);
    ltMainBlock->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    ltMainBlock->addStretch(5);
    ltMainBlock->addWidget(rdxLoadFromFile);
    ltMainBlock->addSpacing(10);
    ltMainBlock->addLayout(ltReview);
    ltMainBlock->addStretch(2);
    ltMainBlock->addWidget(rdxLoadFromGame);
    ltMainBlock->addStretch(5);
    ltMainBlock->addLayout(ltOkAndCancel);
    ltMainBlock->addStretch(1);

    setLayout(ltMainBlock);
}
