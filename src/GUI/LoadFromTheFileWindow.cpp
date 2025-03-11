#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QLineEdit>
#include <QFontMetrics>
#include <QLabel>

#include "../NameOfExt.hpp"
#include "LoadFromTheFileWindow.hpp"

LoadFromTheFileWindow::LoadFromTheFileWindow(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* ltOkAndCancel = new QHBoxLayout();
    QPushButton* btnOk         = new QPushButton(tr("START"));
    QPushButton* btnCancel     = new QPushButton(tr("BACK"));
    QHBoxLayout* ltBtnOk       = new QHBoxLayout();
    QHBoxLayout* ltBtnCancel   = new QHBoxLayout();
    QLabel*      lblSelectFile = new QLabel(tr("Select .csf or .big file:"));

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

    lblSelectFile->setObjectName(nameof(lblSelectFile));
    lblSelectFile->setAlignment(Qt::AlignLeft);

    // configure file path selection
    QLineEdit* lneFilePath = new QLineEdit();
    lneFilePath->setObjectName(nameof(lneFilePath));
    lneFilePath->setMaximumWidth(700);

    QFont font(lneFilePath->font());
    font.setPointSize(font.pointSize()-2); // reduce standart font size
    lneFilePath->setFont(font);

    QFileDialog* fileDialog = new QFileDialog(); // dialog for selecting the path to the file
    fileDialog->setFileMode(QFileDialog::FileMode::ExistingFile);
    fileDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    fileDialog->setNameFilters({tr("Binary files") + " (*.csf *.big)",
                                tr("Any files")  + " (*)"});
    connect(fileDialog, &QFileDialog::fileSelected, lneFilePath, &QLineEdit::setText);
    
    // review button
    QPushButton* btnReview = new QPushButton(tr("REVIEW"));
    btnReview->setObjectName(nameof(btnReview));
    btnReview->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnReview, &QPushButton::clicked, fileDialog, &QFileDialog::exec);

    QHBoxLayout* ltReview = new QHBoxLayout();
    ltReview->addWidget(lneFilePath);
    ltReview->addSpacing(5);
    ltReview->addWidget(btnReview);

    // configure dialog view
    QVBoxLayout* ltMain = new QVBoxLayout();
    ltMain->setContentsMargins(80,0,80,0);
    ltMain->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    ltMain->addStretch(3);
    ltMain->addWidget(lblSelectFile);
    ltMain->addSpacing(5);
    ltMain->addLayout(ltReview);
    ltMain->addStretch(2);
    ltMain->addLayout(ltOkAndCancel);
    ltMain->addStretch(1);

    setLayout(ltMain);
}
