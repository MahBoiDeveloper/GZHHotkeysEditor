#include "loaderwidget.hpp"
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QFontMetrics>
#include <QDebug>

LoaderWidget::LoaderWidget(QWidget *parent)
	: QDialog(parent)
{
	// configure file path selection
	QLineEdit* pathToFileLineEdit = new QLineEdit;
	pathToFileLineEdit->setMaximumWidth(700);
	QFont font(pathToFileLineEdit->font());
	font.setPointSize(font.pointSize()-2); // reduce standart font size
	pathToFileLineEdit->setFont(font);
	QFileDialog* fileDialog = new QFileDialog; // dialog for selecting the path to the file
	fileDialog->setFileMode(QFileDialog::FileMode::ExistingFile);
	fileDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
	fileDialog->setNameFilters({tr("Text files") + "(*.txt)",
								tr("Any files")  + "(*)"});
	connect(fileDialog, &QFileDialog::fileSelected, pathToFileLineEdit, &QLineEdit::setText);
	// review button
	QPushButton* reviewButton = new QPushButton(tr("Review"));
	reviewButton->setStyleSheet("QPushButton { padding-top: 2px; padding-bottom: 2px; }");
	reviewButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	connect(reviewButton, &QPushButton::clicked, fileDialog, &QFileDialog::exec);

	// configure choise buttons
	QRadioButton* loadFromFileButton = new QRadioButton(tr("Load project"));
	connect(loadFromFileButton, &QPushButton::toggled, this,
		[=](bool checked){
			pathToFileLineEdit->setEnabled(checked);
			reviewButton->setEnabled(checked);
		}
	);
	QRadioButton* loadFromGameButton = new QRadioButton(tr("Load installed game hotkey map"));
	groupB.setExclusive(true);
	loadFromFileButton->setChecked(true);
	groupB.addButton(loadFromFileButton);
	groupB.addButton(loadFromGameButton);

	QHBoxLayout* reviewL = new QHBoxLayout;
	reviewL->addWidget(pathToFileLineEdit);
	reviewL->addSpacing(5);
	reviewL->addWidget(reviewButton);
	reviewL->setContentsMargins(loadFromFileButton->sizeHint().width() -
								QFontMetrics(loadFromFileButton->font()).horizontalAdvance(loadFromFileButton->text()),
								0,0,0);

	// configure dialog buttons
	QDialogButtonBox* dialogBB = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	dialogBB->button(QDialogButtonBox::Ok)->setText(tr("Configure"));
	dialogBB->button(QDialogButtonBox::Cancel)->setText(tr("Back"));
	// emit accepted configurations
	connect(dialogBB, &QDialogButtonBox::accepted, this,
		[=](){
			emit acceptedConfiguration(pathToFileLineEdit->text());
		;}
	);
	connect(dialogBB, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);

	// configure dialog view
	QVBoxLayout* mainL = new QVBoxLayout;
	mainL->setContentsMargins(80,0,80,0);
	mainL->setAlignment(Qt::Alignment::enum_type::AlignCenter);
	mainL->addStretch(5);
	mainL->addWidget(loadFromFileButton);
	mainL->addSpacing(10);
	mainL->addLayout(reviewL);
	mainL->addStretch(2);
	mainL->addWidget(loadFromGameButton);
	mainL->addStretch(5);
	mainL->addWidget(dialogBB, 0, Qt::AlignCenter);
	mainL->addStretch(1);
	for(auto & button : dialogBB->buttons())
		button->setStyleSheet("QPushButton { padding-left: 30px; padding-right: 30px; }");
	setLayout(mainL);
}
