#include "mainwidget.hpp"
#include "redactor.hpp"
#include "startWidget/startwidget.hpp"
#include "creatorWidget/creatorwidget.hpp"

MainWidget::MainWidget(QWidget *parent)
	: QStackedWidget(parent)
{
	resize(700,500);
	StartWidget* startWidget = new StartWidget;
	connect(startWidget, &StartWidget::pressed, this,
		[=](int index){
			switch (index) {
			case 0: {
//				addWidget(new Redactor);
				CreatorWidget* creatorWidget = new CreatorWidget;
				addWidget(creatorWidget);
				setCurrentWidget(creatorWidget); // next window (creator)
				break;
			}
			default:
				break;
			}
		}
	);
	addWidget(startWidget);
}

MainWidget::~MainWidget()
{
}
