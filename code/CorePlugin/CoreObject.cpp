#include "CoreObject.h"
#include "StudioView.h"
//#include "HomePageWidget.h"
#include "RenderWidget.h"
#include "../EngineCore/Core/Engine/Node.h"
#include "../EngineCore/Core/Engine/Component.h"
//#include "PropertyWidget.h"
//#include "SolutionWidget.h"
//#include "ResourceViewWidget.h"
//#include "MenuToolBar.h"
//#include "DeepWorldCore/DeepWorldApi/UnitInterface.h"
//#include "KernelInterface/KernelInterface.h"
//#include "ProjectManager/ProjectInclude.h"
#include <QFileInfo>
#include <QStatusBar>
#include <QLabel>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <filesystem>
#include <QSettings>
//#include "CorePluginCommon.h"
//#include "../EngineCore/Serializer/Reference.h"
#include<QMargins>
#include "../SARibbonBar/SARibbonTabBar.h"
#include<QFont>
#include <QSplitter>

#include<QListWidget>
//#include "ItemWidget.h"
//#include "../CyberUniverseGeo/Scene/GeoNode.h"
#include <windows.h>
#include <QPainter>
#include <QtPrintSupport\qprintpreviewdialog.h>
#include <QPrintDialog>
//#include "DeepEyeCore/Graphics/RenderWindow.h"
#include<QScreen>
//#include "../external\Engine\deepeye\src\DeepEyeExt\Log\LogCategory.h"
#include<QPageSetupDialog>
#include<QPrinterInfo>
#include "PropertyWidget.h"
//namespace fs = std::experimental::filesystem;
CoreObject::CoreObject()
{	
	m_studioView = new StudioView();
	m_renderWidget = new RenderWidget(m_studioView);
	m_propertyWidget = new PropertyEditWidget(m_studioView);
}

CoreObject::~CoreObject()
{
	delete m_dockWidMenu;
	delete m_pPrinter;
}

CoreObject* CoreObject::instance()
{
	static CoreObject obj;
	return &obj;
}
void CoreObject::addDockWidget(Qt::DockWidgetArea area, QDockWidget* widget)
{
	m_studioView->addTabifiedDockWidget(area, widget);
}

void CoreObject::init()
{
	m_studioView->show();

	auto frameWidget = new QWidget;
	m_studioView->setCentralWidget(frameWidget);

	QSplitter* frameSpliter = new QSplitter;
	frameSpliter->setOrientation(Qt::Horizontal);

	auto frameLayout = new QVBoxLayout;
	frameLayout->addWidget(frameSpliter);
	frameLayout->setContentsMargins(0, 0, 0, 0);

	frameWidget->setLayout(frameLayout);

	m_studioView->addTabifiedDockWidget(Qt::RightDockWidgetArea, m_propertyWidget);

	auto layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(m_renderWidget);

	auto centralWidget = new QWidget;
	centralWidget->setLayout(layout);

	frameSpliter->addWidget(m_renderWidget);
	frameSpliter->setHandleWidth(3);

	// Connect property changes → D3D11 resource update → repaint
	connect(m_propertyWidget, &PropertyEditWidget::propertyChanged, [this]() {
		auto node = m_propertyWidget->getNode();
		if (node)
		{
			for (size_t i = 0; i < node->getComponentCount(); ++i)
			{
				auto comp = node->getComponent(i);
				if (comp) comp->applyChanges();
			}
		}
		m_renderWidget->update();
	});
}

//�˴���QMainWindow��ΪSARibbonMainWindow,��ΪStudioViewֱ�Ӽ̳�SARibbonMainWindow
SARibbonMainWindow* CoreObject::getMainWindow()
{
	return m_studioView;
}


void CoreObject::nodeSelectChangle(EngineCore::Scene* scene, std::vector<EngineCore::Node*>& nodes)
{
	std::vector<EngineCore::Node*>& selNodes = nodes;

	if (selNodes.size())
	{
		EngineCore::Node* cursorNode = selNodes.back();
		m_propertyWidget->setNode(cursorNode);
	}
}

