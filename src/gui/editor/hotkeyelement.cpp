#include "hotkeyelement.h"
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDebug>

void HotkeyElement::keyPressEvent(QKeyEvent* event)
{
	int key = event->key();
	if (key >= Qt::Key_A && key <= Qt::Key_Z) {
		hotkeyLb.setText(QKeySequence(key).toString());
		// unset decoration
		hotkeyLb.setFont(QFont());
		hotkeyLb.setPalette(QPalette());
		// return focus to parent
		parentWidget()->setFocus();
	} else
		qDebug() << "no";
	QWidget::keyPressEvent(event);
}

HotkeyElement::HotkeyElement(const QString& actionName, const QString& hotkeyStr, QWidget* parent)
	: QWidget(parent)
	, actionNameLb(actionName)
	, hotkeyLb(hotkeyStr)
{
	hotkeyLb.setAlignment(Qt::AlignCenter);
	hotkeyLb.setStyleSheet("padding-left: 30px; padding-right: 30px; background-color: gray");
	QPushButton* newHotkeyB = new QPushButton("+");
	// square button
	newHotkeyB->setFixedSize(newHotkeyB->sizeHint().height(), newHotkeyB->sizeHint().height());
	// suggest entering a hotлун
	connect(newHotkeyB, &QPushButton::pressed, this,
			[this]()
			{
				// decoration
				hotkeyLb.setText(tr("press the letter key"));
				QFont f(hotkeyLb.font());
				f.setItalic(true);
				hotkeyLb.setFont(f);
				QPalette p;
				p.setColor(QPalette::WindowText, Qt::GlobalColor::cyan);
				hotkeyLb.setPalette(p);
				setFocus(); // set focus to current action
			}
	);

	QHBoxLayout* mainL = new QHBoxLayout(this);
	mainL->setAlignment(Qt::AlignTop);
	mainL->addWidget(&actionNameLb);
	mainL->setStretch(0, 1);
	mainL->addWidget(&hotkeyLb);
	mainL->addWidget(newHotkeyB);
	setLayout(mainL);
}

QString HotkeyElement::getActionName() const
{
	return actionNameLb.text();
}

QString HotkeyElement::getHotkey() const
{
	return hotkeyLb.text();
}
