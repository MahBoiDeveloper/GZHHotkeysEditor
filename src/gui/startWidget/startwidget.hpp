#pragma once
#include <QWidget>
#include "pushbutton.hpp"
#include "../configurations.hpp"
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
	StartWidget(configurations::Languages language = configurations::Languages::English, QWidget *parent = nullptr);
	~StartWidget();

signals:
	void resized(int h);
	void pressed(int index);
	void languageChanged(int index);
};
