#include <QDialogButtonBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QFontMetrics>

#include "LoadDialog.hpp"

LoadDialog::LoadDialog(QWidget* parent) : BaseConfigurationDialog(parent)
{
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
    QRadioButton* loadFromFileButton = new QRadioButton(tr("Load project"));
    connect(loadFromFileButton, &QPushButton::toggled, this, [=, this](bool checked)
    {
        pathToFileLineEdit->setEnabled(checked);
        btnReview->setEnabled(checked);
    });

    QRadioButton* loadFromGameButton = new QRadioButton(tr("Load installed game hotkey map"));
    buttonsGroup.setExclusive(true);
    loadFromFileButton->setChecked(true);
    buttonsGroup.addButton(loadFromFileButton);
    buttonsGroup.addButton(loadFromGameButton);

    QHBoxLayout* ltReview = new QHBoxLayout();
    ltReview->addWidget(pathToFileLineEdit);
    ltReview->addSpacing(5);
    ltReview->addWidget(btnReview);
    ltReview->setContentsMargins(loadFromFileButton->sizeHint().width() -
                                QFontMetrics(loadFromFileButton->font()).horizontalAdvance(loadFromFileButton->text()),
                                0,0,0);

    // configure dialog view
    QVBoxLayout* ltMainBlock = new QVBoxLayout();
    ltMainBlock->setContentsMargins(80,0,80,0);
    ltMainBlock->setAlignment(Qt::Alignment::enum_type::AlignCenter);
    ltMainBlock->addStretch(5);
    ltMainBlock->addWidget(loadFromFileButton);
    ltMainBlock->addSpacing(10);
    ltMainBlock->addLayout(ltReview);
    ltMainBlock->addStretch(2);
    ltMainBlock->addWidget(loadFromGameButton);
    ltMainBlock->addStretch(5);
    ltMainBlock->addWidget(&dialogButtons, 0, Qt::AlignCenter);
    ltMainBlock->addStretch(1);
    setLayout(ltMainBlock);
}

QVariant LoadDialog::CreateConfigurationData() { return QVariant("Loader widget data."); }
