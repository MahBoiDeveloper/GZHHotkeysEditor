#include <QDialogButtonBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QLineEdit>
#include <QFontMetrics>

#include "LoadDialog.hpp"

LoadDialog::LoadDialog(QWidget* parent) : QDialog(parent)
{
    QDialogButtonBox* btnbxOkAndCancel = new QDialogButtonBox();
    btnbxOkAndCancel->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    btnbxOkAndCancel->button(QDialogButtonBox::Ok)->setText(tr("START"));
    btnbxOkAndCancel->button(QDialogButtonBox::Cancel)->setText(tr("BACK"));
    connect(btnbxOkAndCancel, &QDialogButtonBox::rejected, this, [=, this] { emit btnBackClicked(); });
    connect(btnbxOkAndCancel, &QDialogButtonBox::accepted, this, [=, this] { emit btnStartClicked(); });

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
    btnReview->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnReview, &QPushButton::clicked, fileDialog, &QFileDialog::exec);

    // configure choise buttons
    QRadioButton* rdxLoadFromFile = new QRadioButton(tr("Load project"));
    connect(rdxLoadFromFile, &QPushButton::toggled, this, [=, this](bool checked)
    {
        pathToFileLineEdit->setEnabled(checked);
        btnReview->setEnabled(checked);
    });

    QButtonGroup* btngRadioboxes = new QButtonGroup();
    QRadioButton* rbxLoadFromGame = new QRadioButton(tr("Load installed game hotkey map"));
    btngRadioboxes->setExclusive(true);
    rdxLoadFromFile->setChecked(true);
    btngRadioboxes->addButton(rdxLoadFromFile);
    btngRadioboxes->addButton(rbxLoadFromGame);

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
    ltMainBlock->addWidget(rbxLoadFromGame);
    ltMainBlock->addStretch(5);
    ltMainBlock->addWidget(btnbxOkAndCancel, 0, Qt::AlignCenter);
    ltMainBlock->addStretch(1);

    setLayout(ltMainBlock);
}
