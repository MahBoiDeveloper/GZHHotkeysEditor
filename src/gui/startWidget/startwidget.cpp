#include "startwidget.hpp"
#include <QButtonGroup>
#include <QLayout>
#include <QResizeEvent>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QComboBox>
#include <QLabel>

PushButton* StartWidget::initButton(const QString& name) const
{
	PushButton* button = new PushButton(name);
    button->setMaximumHeight(250);
	button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(this, &StartWidget::resized, button,
		[button](int height){
			button->setFixedHeight(button->getBaseHeight() + height/10);
        }
	);
    return button;
}

void StartWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	emit resized(event->size().height());
}

StartWidget::StartWidget(configurations::Languages language, QWidget *parent)
	: QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	bg = new QButtonGroup;
	bg->addButton(initButton(tr("NEW HOTKEY MAP")));
	bg->addButton(initButton(tr("LOAD HOTKEY MAP")));
    connect(bg, QOverload<int>::of(&QButtonGroup::idClicked), this,
        [=](int id){
			int index = (-1)*id - 2; // QButtonGroup assign index -2 to first button
			emit StartWidget::pressed(index);
        }
    );
	QComboBox* langBox = new QComboBox;
	langBox->addItem("English");
	langBox->addItem("Русский");
	langBox->setCurrentIndex(static_cast<int>(language));
//	langBox->setContentsMargins(10, 0, 10, 0);
	connect(langBox, QOverload<int>::of(&QComboBox::activated), this, &StartWidget::languageChanged);
	QLabel* languageName = new QLabel(tr("Language"));
	QHBoxLayout* languageL = new QHBoxLayout;
	languageL->addWidget(languageName);
	languageL->addSpacing(5);
	languageL->addWidget(langBox);
	languageL->setAlignment(Qt::AlignRight);

    QVBoxLayout* vl = new QVBoxLayout;
	vl->addStretch(5);
    // vl->addSpacerItem(new QSpacerItem(10, 100, QSizePolicy::Minimum, QSizePolicy::Maximum));
	vl->addWidget(bg->buttons().at(0));
	vl->addStretch(2);
    // vl->addSpacerItem(new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	vl->addWidget(bg->buttons().at(1));
    // vl->addSpacerItem(new QSpacerItem(10, 100, QSizePolicy::Minimum, QSizePolicy::Maximum));
	vl->addStretch(5);
    vl->setContentsMargins(70, 10, 70, 30);
    vl->setAlignment(Qt::AlignCenter);
	vl->addLayout(languageL);
//	vl->setSpacing(30);
	setLayout(vl);
}

StartWidget::~StartWidget()
{
}
