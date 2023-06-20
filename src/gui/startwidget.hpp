#pragma once
#include <QWidget>
#include "pushbutton.h"
//#include <QPushButton>

class StartWidget : public QWidget
{
	Q_OBJECT
private:
	QButtonGroup* bg;

private:
	PushButton* initButton(const QString& name) const;
	void resizeEvent(QResizeEvent *event) override;

public:
	StartWidget(QWidget *parent = nullptr);
	~StartWidget();

signals:
	void resized(int h);
	void pressed(int index);
};
