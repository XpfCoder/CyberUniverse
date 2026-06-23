#include "UserInfoWidget.h"
#include <QPainter>
#include "CoreObject.h"
#include "PluginManager.h"
#include <QToolBar>
UserInfoWidget::UserInfoWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(u8"用户登录");
	init();

	connect(ui.offlineButton, &QPushButton::clicked, this, &UserInfoWidget::onOpenCyberUniverseStudio);
}

UserInfoWidget::~UserInfoWidget()
{}

void UserInfoWidget::initUserInfo()
{
	//CommonInfoSQLite* pCommonInfoSQLite = CommonInfoSQLite::GetInstance();
	//if (!pCommonInfoSQLite)
	//{
	//	LogErrorEx(__FUNCTION__, ": common info sqlite is nullptr.");
	//	return;
	//}

	//pCommonInfoSQLite->getUserNameInfoList(m_strResult);
	if (!m_strResult.empty())
	{
		std::map<std::string, std::string> userMap = m_strResult[0];
		ui.userNameComboBox->setEditText(userMap["name"].c_str());
		if (userMap["remember"] == "1")
		{
			ui.rememberPwdCheck->setChecked(true);
			ui.passwordEdit->setText(userMap["pwd"].c_str());
		}
		else
			ui.rememberPwdCheck->setChecked(false);
	}

}

void UserInfoWidget::init()
{
	ui.errorEdit->hide();
	ui.passwordEdit->setPlaceholderText(u8"密码");
	m_userNameEdit = new QLineEdit;
	m_userNameEdit->setPlaceholderText(u8"用户名");
	ui.userNameComboBox->setLineEdit(m_userNameEdit);
	ui.userNameComboBox->setMaxVisibleItems(4);

	ui.passwordEdit->setEchoMode(QLineEdit::Password);

	QAction * userNameAction = new QAction(m_userNameEdit);
	userNameAction->setIcon(QIcon(":/CorePlugin/Resources/11.png"));
	m_userNameEdit->addAction(userNameAction, QLineEdit::LeadingPosition);

	QAction * passwordAction = new QAction(ui.passwordEdit);
	passwordAction->setIcon(QIcon(":/CorePlugin/Resources/12.png"));
	ui.passwordEdit->addAction(passwordAction, QLineEdit::LeadingPosition);


	m_showPasswordAction = new QAction(ui.passwordEdit);
	m_showPasswordAction->setIcon(QIcon(":/CorePlugin/Resources/14.png"));
	ui.passwordEdit->addAction(m_showPasswordAction, QLineEdit::TrailingPosition);


	m_showPasswordAction->setCheckable(true);
	connect(m_showPasswordAction, &QAction::toggled, [this](bool checked) {
		if (checked)
		{
			ui.passwordEdit->setEchoMode(QLineEdit::Normal);
			m_showPasswordAction->setIcon(QIcon(":/CorePlugin/Resources/13.png"));
		}
		else
		{
			ui.passwordEdit->setEchoMode(QLineEdit::Password);
			m_showPasswordAction->setIcon(QIcon(":/CorePlugin/Resources/14.png"));
		}
		});
}

void UserInfoWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/CorePlugin/Resources/2.png"));
}

void UserInfoWidget::onOpenCyberUniverseStudio()
{
	auto coreObject = CoreObject::instance();
	coreObject->init();

	//coreObject->getMainWindow()->setMenuWidget(new SARibbonBar(this));


	auto pluginManager = Resafety::CyberUniverseStudio::PluginManager::instance();
	pluginManager->load();

	emit hideLogin();
	//emit coreObject->onLine(true);

}