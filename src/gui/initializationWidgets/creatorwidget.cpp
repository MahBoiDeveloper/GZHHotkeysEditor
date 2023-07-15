#include "creatorwidget.hpp"
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>

CreatorWidget::CreatorWidget(QWidget *parent)
	: QDialog(parent)
{
	// configure game buttons
	QRadioButton* generalsButton = new QRadioButton(
				QString::fromStdString(Helper::GameEnumToString(Helper::GAMES::GENERALS)));
	QRadioButton* zeroHourButton = new QRadioButton(
				QString::fromStdString(Helper::GameEnumToString(Helper::GAMES::GENERALS_ZERO_HOUR)));
	groupB.setExclusive(true);
	generalsButton->setChecked(true);
	groupB.addButton(generalsButton);
	groupB.addButton(zeroHourButton);
	QVBoxLayout* choiseL = new QVBoxLayout;
	choiseL->addWidget(generalsButton);
	choiseL->addWidget(zeroHourButton);

	// configure save option
	saveToGameBox.setText(tr("Save hotkeys dirrectly to the game"));

	// configure dialog buttons
	QDialogButtonBox* dialogBB = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	dialogBB->button(QDialogButtonBox::Ok)->setText(tr("Configure"));
	dialogBB->button(QDialogButtonBox::Cancel)->setText(tr("Back"));
	// emit accepted configurations
	connect(dialogBB, &QDialogButtonBox::accepted, this,
		[=](){
			emit acceptedConfiguration(static_cast<Helper::GAMES>(groupB.checkedId()),
																  saveToGameBox.isChecked());
		;}
	);
	connect(dialogBB, &QDialogButtonBox::rejected, this, &QDialog::deleteLater);

	// configure dialog view
	QVBoxLayout* mainL = new QVBoxLayout;
	mainL->setAlignment(Qt::Alignment::enum_type::AlignCenter);
	mainL->addStretch(5);
	mainL->addLayout(choiseL);
	mainL->addStretch(2);
	mainL->addWidget(&saveToGameBox);
	mainL->addStretch(5);
	mainL->addWidget(dialogBB, 0, Qt::AlignCenter);
	mainL->addStretch(1);
	for(auto & button : dialogBB->buttons())
		button->setStyleSheet("QPushButton { padding-left: 30px; padding-right: 30px; }");
	setLayout(mainL);
}
