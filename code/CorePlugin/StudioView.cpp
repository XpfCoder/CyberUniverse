#include "StudioView.h"
#include <QApplication>
#include <QFile>
#include <QTextEdit>
#include <QAbstractButton>
#include <QFileDialog>
#include "../SARibbonBar/SARibbonBar.h"
#include "../SARibbonBar/SARibbonCategory.h"
#include <QPushButton>
#include <QMessageBox>
#include "../SARibbonBar/SARibbonPannel.h"
#include "../SARibbonBar/SARibbonToolButton.h"
#include <QAction>
#include <QMenu>
#include <QStatusBar>
#include <QDebug>
#include <QElapsedTimer>
#include <QRadioButton>
#include <QButtonGroup>
#include "../SARibbonBar/SARibbonMenu.h"
#include "../SARibbonBar/SARibbonComboBox.h"
#include "../SARibbonBar/SARibbonLineEdit.h"
#include "../SARibbonBar/SARibbonGallery.h"
#include "../SARibbonBar/SARibbonCheckBox.h"
#include "../SARibbonBar/SARibbonQuickAccessBar.h"
#include "../SARibbonBar/SARibbonButtonGroupWidget.h"
#include "../SARibbonBar/SARibbonApplicationButton.h"
#include "../SARibbonBar/SARibbonCustomizeWidget.h"
#include "../SARibbonBar/SARibbonElementManager.h"
#include <QCalendarWidget>
#include "../SARibbonBar/SARibbonCustomizeDialog.h"
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QFontComboBox>
#include <QLabel>
#include "../SARibbonBar/SAFramelessHelper.h"

#pragma execution_character_set("utf-8")

StudioView::StudioView()
	: SARibbonMainWindow(nullptr)
{
	setWindowTitle(u8"CyberUniverse Studio");
	//setMinimumSize(1280, 720);
	setWindowState(Qt::WindowMaximized);

	QFile AppStyleFile(u8"../CyberUniverse/qss/dwblack.css");
	bool ll = AppStyleFile.open(QIODevice::ReadOnly);
	static_cast<QApplication*>(QCoreApplication::instance())->setStyleSheet(AppStyleFile.readAll());

	SAFramelessHelper* helper = framelessHelper();
	helper->setRubberBandOnResize(false);

	setStatusBar(new QStatusBar());

	SARibbonBar* ribbon = ribbonBar();
	//通过setContentsMargins设置ribbon四周的间距
	ribbon->setContentsMargins(5, 0, 5, 0);
	//设置applicationButton

	ribbon->applicationButton()->setText(("文件"));

	//添加主标签页 - 通过addCategoryPage工厂函数添加
	SARibbonCategory* categoryMain = ribbon->addCategoryPage(tr("主要"));
	categoryMain->setObjectName(("categoryMain"));
	categoryMain->hide();
	//添加其他标签页 - 直接new SARibbonCategory添加
	SARibbonCategory* categoryTool = new SARibbonCategory();
	categoryTool->setCategoryName(tr("工具"));
	categoryTool->setObjectName(("categoryTool"));
	categoryTool->hide();
	//createCategoryOther(categoryOther);
	ribbon->addCategoryPage(categoryTool);


	//添加删除标签页
	SARibbonCategory* categoryDelete = new SARibbonCategory();
	categoryDelete->setContentsMargins(50, 50, 50, 50);
	categoryDelete->setCategoryName(tr("删除"));
	categoryDelete->setObjectName(("categoryDelete"));

	categoryDelete->hide();
	ribbon->addCategoryPage(categoryDelete);

	SARibbonCategory* categorySize = new SARibbonCategory();

	categorySize->setCategoryName(("编辑"));
	categorySize->setObjectName(tr("categoryEditor"));
	categorySize->setSizeIncrement(5,8);
	categorySize->hide();
	ribbon->addCategoryPage(categorySize);


	setMinimumWidth(500);

	//showMaximized();
	SARibbonPannel* ToolPannel = new SARibbonPannel();
	ToolPannel->setObjectName(QString::fromStdString("常用工具"));
	ToolPannel->setWindowTitle(QString::fromStdString("常用工具"));

	QAction* actLocateRibbon = createAction(tr("定位"), ":/CorePlugin/Resources/logo.png", "定位");
	actLocateRibbon->setCheckable(true);
	ToolPannel->addLargeAction(actLocateRibbon);

	categoryTool->addPannel(ToolPannel);


	this->ribbonBar()->setMinimumMode(true);

	setWindowIcon(QIcon(":/CorePlugin/Resources/logo.png"));//可执行程序图标
	QMenu* spawnerMenu = new QMenu(u8"地形编辑");
	this->menuBar()->addMenu(spawnerMenu);
	ribbon->showMinimumModeButton();
}

StudioView::~StudioView()
{}

QAction* StudioView::createAction(const QString& text, const QString& iconurl)
{
	QAction* act = new QAction(this);
	act->setText(text);
	act->setIcon(QIcon(iconurl));
	act->setObjectName(text);
	return act;
}

QAction* StudioView::createAction(const QString& text, const QString& iconurl, const QString& objName)
{
	QAction* act = new QAction(this);
	act->setText(text);
	act->setIcon(QIcon(iconurl));
	act->setObjectName(objName);
	return act;
}

void StudioView::addTabifiedDockWidget(Qt::DockWidgetArea area, QDockWidget* dockwidget)
{
	addDockWidget(area, dockwidget);
	//int count = tabifiedDockWidgets(dockwidget).count();
	for (auto firstWidget : m_dockWidgets)
	{
		if (dockWidgetArea(firstWidget) == area)
		{
			if (tabifiedDockWidgets(dockwidget).count() == 0)
			{
				tabifyDockWidget(firstWidget, dockwidget);
			}
			else
			{
				auto backWidget = tabifiedDockWidgets(firstWidget).back();
				tabifyDockWidget(backWidget, dockwidget);
			}
			break;
		}
	}
	m_dockWidgets.append(dockwidget);
}
