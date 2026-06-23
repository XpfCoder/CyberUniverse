#include "LoginWidget.h"
#include <QPainter>
#include <QLayout>
#include <filesystem>
#include <QLibrary>
#include "UserInfoWidget.h"


//namespace fs = std::experimental::filesystem;

LoginWidget::LoginWidget(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
	init();

	QString appPath = QCoreApplication::applicationDirPath();
	std::string exePath = appPath.toStdString();

	//KernelEnvironment env;
	//env.exePath = exePath + "/";
	//KernelInterface::GetInstance()->setEnvironment(env);
	setWindowIcon(QIcon(":/CorePlugin/Resources/logo.png"));//可执行程序图标
	
}
LoginWidget:: ~LoginWidget()
{

}

void LoginWidget::init()
{
	ui.setupUi(this);
	setWindowTitle(u8"CyberUniverse Studio");
	setAttribute(Qt::WA_DeleteOnClose);
	resize(1800, 950);
	ui.label->setText(u8"当前版本：v1.0.1");

	m_online = new UserInfoWidget();
	connect(m_online, &UserInfoWidget::hideLogin, this, &LoginWidget::close);
	ui.verticalLayout_2->addWidget(m_online);

}

void LoginWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/CorePlugin/Resources/1.jpg"));
}

