#pragma once
#include "ui_UserInfoWidget.h"
#include <QWidget>
#include <QAction>

class UserInfoWidget  : public QWidget
{
	Q_OBJECT
public:
	UserInfoWidget(QWidget* parent = nullptr);
	~UserInfoWidget();

private slots:
	//bool onOpenOnlineWidget();
	void onOpenCyberUniverseStudio();
	//void onOpenUrl();
	//void onShowAccountInfo(int index, QString accountName);
	//void onRemoveAccont(int index);

signals:
	//void offline(bool is);
	//void offlineToOnline();
	//void line();
	void hideLogin();

protected:
	void initUserInfo();
	//void initUserAndUrlList();
	//void saveUserInfoTotable();
	//bool isRememberPwd();
	void init();
	//QString showErrorMsg(std::string errorMessage); private:
	void paintEvent(QPaintEvent *e);

private:
	Ui::UserInfoWidget ui;
	std::vector<std::map<std::string, std::string>> m_strResult;
	QLineEdit * m_addressEdit;
	QLineEdit * m_userNameEdit;
	QAction *m_showPasswordAction;
};
