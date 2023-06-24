#include "creatorwidget.hpp"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>

CreatorWidget::CreatorWidget(QWidget *parent)
	: QDialog(parent)
{
	QRadioButton* generalsButton = new QRadioButton(tr("Generals"));
	QRadioButton* zeroHourButton = new QRadioButton(tr("Generals Zero Hour"));
	QButtonGroup* groupB = new QButtonGroup;
	groupB->setExclusive(true);
	generalsButton->setChecked(true);
	groupB->addButton(generalsButton);
	groupB->addButton(zeroHourButton);
	QVBoxLayout* choiseL = new QVBoxLayout;
	choiseL->addWidget(generalsButton);
	choiseL->addWidget(zeroHourButton);

	QCheckBox* saveToGameBox = new QCheckBox(tr("Save hotkey dirrectly to the game"));

//	QPushButton* startButton = new QPushButton(tr("Start configurating"));
//	startButton->setStyleSheet("padding: 10px;"); // spacing between border and text

	QDialogButtonBox* dialogBB = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	dialogBB->button(QDialogButtonBox::Ok)->setText(tr("Start configurating"));
	dialogBB->button(QDialogButtonBox::Cancel)->setText(tr("Back"));
	connect(dialogBB, &QDialogButtonBox::accepted, this, &QDialog::accepted);
	connect(dialogBB, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);

	QVBoxLayout* mainL = new QVBoxLayout;
	mainL->setAlignment(Qt::Alignment::enum_type::AlignCenter);
	mainL->addStretch(5);
	mainL->addLayout(choiseL);
	mainL->addStretch(2);
	mainL->addWidget(saveToGameBox);
//	mainL->addStretch(2);
//	mainL->addWidget(startButton);
	mainL->addStretch(5);
	mainL->addWidget(dialogBB, 0, Qt::AlignCenter);
	mainL->addStretch(1);
//	mainL->setSizeConstraint(QLayout::SetFixedSize);
	dialogBB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//	dialogBB->setStyleSheet("QPushButton { padding: 20px; }");
	for(auto & button : dialogBB->buttons())
		button->setStyleSheet("QPushButton { padding-left: 30px; padding-right: 30px; }");
	setLayout(mainL);

}
