#pragma once
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include "ui_Login.h"
#include "UserInfoWidget.h"

class LoginWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LoginWidget(QWidget* parent = Q_NULLPTR);
	~LoginWidget();
public:
	void paintEvent(QPaintEvent *e);

protected:
	void init();

private:
	Ui::Login ui;
	UserInfoWidget* m_online;
	//std::string m_errorMsg{ "" };
	//std::string m_requirCode{ "" };
};
#endif