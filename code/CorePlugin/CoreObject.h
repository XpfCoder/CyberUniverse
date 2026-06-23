/************************************
Copyright:北京睿呈时代信息科技有限公司 
Author: lihongchao
Date:2020/09/09 17:27
Description: 核心访问接口实现类
************************************/
#pragma once
#include "ICore.h"
#include "../SARibbonBar/SARibbonMainWindow.h"
#include "../SARibbonBar/SARibbonQuickAccessBar.h"
#include "../SARibbonBar/SARibbonBar.h"
#include <QtPrintSupport\qprinter.h>
#include <QDockWidget>

#pragma execution_character_set("utf-8")//让能够正常显示中文字符串

class StyleAlter;
class StudioView;
class HomePageWidget;
class RenderWidget;
class PropertyEditWidget;
class MenuToolBar;
class SolutionWidget;
class ResourceViewWidget;
class Scene;
namespace EngineCore { class Reference; };
class CoreObject : public QObject, public Resafety::CyberUniverseStudio::ICore
{
	Q_OBJECT
private:
	CoreObject();
	~CoreObject();
	CoreObject(const CoreObject&) = delete;
	CoreObject& operator=(const CoreObject&) = delete;

public:
	static CoreObject* instance();
public slots:
	//void showRibbonBarRmenu(const QPoint& point);
	//void alterStyle();
	//void setEnableFileWatch(bool enable);

	//void layerValueChange(std::string guid);

	//void updateDir(const QString& dir);


	//打印
	//void Preview(QPrinter* printer);
public:
	//////////////////////////////////////////////////////////////////////////
	// 实现接口

	// 添加停靠窗口
	void addDockWidget(Qt::DockWidgetArea area, QDockWidget* widget) override;

	// 添加工具栏
	//void addToolBar(QToolBar *toolbar) override;

	// 获取菜单栏
	//QMenuBar* menuBar() const override;

	// 获取状态栏
	//QStatusBar* statusBar() const override;	

	// 添加回撤命令
	//void pushUndoCommand(QUndoCommand* command) override;

	// 设置对象
	// 设置后会通知所有监听者
	//void setObject(IUnit* obj) override;

	//设置场景节点
	//void setSceneNode(void* obj) override;

	void nodeSelectChangle(EngineCore::Scene* scene, std::vector<EngineCore::Node*>& nodes) override;
	// 设置对象监听
	// 回调函数参数为新的对象
	//void listenObjectChanged(const std::function<void(IUnit*)>& onChanged) override;

	// 回调函数参数为新的对象-基础场景节点
	//void listenNodeTxt(const std::function<void(QString)>& onStrText) override;
	//void notifytNodeTxt(QString& strText) override;

	// 输出消息
	//void outputMessage(const QString& msg) override;

	// 刷新
	//QAction* refreshAction() const override;

	//QAction* getAction(const QString& actionName) const override;
	
	// 注册事件回调
	//void registerEventCallback(const QString& key, const std::function<void(int x, int y)>& func);
	//void unRegisterEventCallback(const QString& key);
	//void registerCallback(const std::function<void(int)>& func);

	// 注册事件回调--用于uploadPG
	//void registerEventCallbacktoUploadPG(const QString& key, const std::function<void()>& func);
	//void  runUpload();

	//void renderWidgetEvent(const QString& key, const QPoint& point);
	//void notifyDropEvent(int type);

	SARibbonMainWindow* getMainWindow() override;
	//RenderWidget* getRenderWidget();

	//void resizeRenderWidget(uint32_t width, uint32_t height) override;

	//void registerPluginCallback(const QString& key, std::function<void(int type, QStringList& ret)> func);
	//void unRegisterPluginCallback(const QString& key);
	//void notifyPluginEvent(const QString& key, int type, QStringList& ret);

	//void registerClosePluginCallback(const QString& pluginName, const std::function<void()>& closeFunction) override;
	//void unRegisterClosePluginCallback(const QString& pluginName) override;

	//void setResourceWidgetVisible(bool visible);


	//virtual void setPluginInterface(Resafety::CyberUniverseStudio::ILayerManager* obj) override;
	//virtual Resafety::CyberUniverseStudio::ILayerManager* getPluginInterface() override;

	//void bindUpdateSceneView(const std::function<void(pafcore::Reference* reference)>& func);
public:
	void init();
	//QList<QToolBar*>getListToolBar();  //获取保存的工具条List
	//void expendPluginAlter();  //将扩展插件的风格转换

	//打印
	//void onPrintPreview();
	//void onPrint();
	//void onPrintSet();

	//用于保存添加的ToolBar
	QList<QToolBar*> m_lstToolBar;
	QList<QString> m_historyName;
	//void showStyle();
signals:
	//void tokenList(QStringList list);
	void onLine(bool is);
	//void line();
private:
	StudioView* m_studioView;
	HomePageWidget* m_homePageWidget;
	MenuToolBar* m_menuToolBar;
	SolutionWidget* m_solutionWidget;
	RenderWidget* m_renderWidget;
	ResourceViewWidget* m_resourceWidget;
	PropertyEditWidget* m_propertyWidget{ nullptr };

	IUnit* m_object{ nullptr };
	using Listener = std::function<void(IUnit*)>;
	std::vector<Listener> m_listeners;
	using DropPositioner = std::function<void(int x, int y)>;
	using DropFunc = std::function<void(int ty)>;
	using UploadFunc = std::function<void()>;//添加上传PG的回调函数
	std::map<QString, DropPositioner> m_eventCallbacks;
	std::vector<DropFunc> m_callbacks;
	std::map<QString, UploadFunc> m_uploadCallbacks;//上传PG的回调函数列表

	using PluginNotifyFunc = std::function<void(int type, QStringList& ret)>;
	std::map<QString, PluginNotifyFunc> m_pluginCallbacks;


	
	static QList<QAction*> s_lstAction;
	StyleAlter* m_styleAlter = NULL;
	QMenu* m_dockWidMenu;
	QList<QDockWidget*> m_dockWidgetLst;
	QList<QAction*>m_dockWigActLst;

	Resafety::CyberUniverseStudio::ILayerManager* m_layerManager{ nullptr };

	using ListenerNodeTxt = std::function<void(QString strText)>;
	std::vector<ListenerNodeTxt> m_NodeTxtlisteners;

	//打印
	QPrinter* m_pPrinter;
	//using valueChange = std::function<void(std::string guid)>;
	//valueChange m_valueChanged;
	std::function<void(std::string guid)> m_valueChanged;
};
