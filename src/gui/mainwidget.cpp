#include "mainwidget.hpp"
#include "redactor.hpp"
#include "startwidget.hpp"

MainWidget::MainWidget(QWidget *parent)
	: QStackedWidget(parent)
{
	resize(700,500);
	StartWidget* firstWidget = new StartWidget;
	connect(firstWidget, &StartWidget::pressed, this,
		[=](int index){
			switch (index) {
			case 0:
				addWidget(new Redactor);
				setCurrentWidget(widget(indexOf(currentWidget())+1)); // next window (redactor)
				break;
			default:
				break;
			}
		}
	);
	addWidget(firstWidget);
}

MainWidget::~MainWidget()
{
}
