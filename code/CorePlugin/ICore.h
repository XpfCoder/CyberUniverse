/************************************
Copyright:北京睿呈时代信息科技有限公司 
Author: lihongchao
Date:2020/09/09 17:21
Description: DeepWorldStudio的核心访问接口
************************************/
#pragma once
#include <QMainWindow>
#include <QUndoCommand> 
#include <functional>

namespace pafcore
{
	class Reference;
}
class IUnit;
namespace Resafety {
	namespace CyberUniverseStudio {
		class ILayerManager;
	}
}

namespace EngineCore { class Scene; };
namespace EngineCore { class Node; };
namespace Resafety {
namespace CyberUniverseStudio {
	
class ICore
{
public:
	// 添加停靠窗口
	virtual void addDockWidget(Qt::DockWidgetArea area, QDockWidget* widget) = 0;

	// 添加工具栏
	//virtual void addToolBar(QToolBar *toolbar) = 0;

	// 获取菜单栏
	//virtual QMenuBar* menuBar() const = 0;

	// 获取状态栏
	//virtual QStatusBar* statusBar() const = 0;

	// 添加回撤命令
	//virtual void pushUndoCommand(QUndoCommand* command) = 0;

	// 设置对象
	// 设置后会通知所有监听者
	//virtual void setObject(IUnit* obj) = 0;

	//设置场景节点
	//virtual void setSceneNode(void* node) = 0;

	virtual void nodeSelectChangle(EngineCore::Scene* scene, std::vector<EngineCore::Node*>& nodes) = 0;
	// 设置对象监听
	// 回调函数参数为新的对象
	//virtual void listenObjectChanged(const std::function<void(IUnit*)>& onChanged) = 0;	

	// 回调函数参数为新的对象-基础场景节点
	//virtual void listenNodeTxt(const std::function<void(QString)>& onStrText) = 0;
	//virtual void notifytNodeTxt(QString& strText) = 0;

	// 输出消息
	//virtual void outputMessage(const QString& msg) = 0;

	// 刷新
	//virtual QAction* refreshAction() const = 0;

	//获取Action
	//virtual QAction* getAction(const QString& actionName) const = 0;

	// 注册事件回调
	//virtual void registerEventCallback(const QString& key, const std::function<void(int x, int y)>& func) = 0;
	//virtual void registerCallback(const std::function<void(int)>& func) = 0;

	virtual QMainWindow* getMainWindow() = 0;

	//virtual void registerPluginCallback(const QString& key, std::function<void(int type, QStringList& ret)> func) = 0;
	//virtual void notifyPluginEvent(const QString& key, int type, QStringList& ret) = 0;

	//各插件注册关闭时事件回调
	//比如打开A插件进行某些工作，但是没有点击A插件内的保存按钮，直接studio的关闭按钮，这时也需要提示用户A插件
	//还有为完成的工作，是否需要保存
	//virtual void registerClosePluginCallback(const QString& pluginName, const std::function<void()>& closeFunction) = 0;

	//各插件反注册关闭时的事件回调；如果插件自己保存了相关工作，需要反注册，不需要studio关闭时处理
	//virtual void unRegisterClosePluginCallback(const QString& pluginName) = 0;

	//// 注册事件回调--用于uploadPG
	//virtual void registerEventCallbacktoUploadPG(const QString& key, const std::function<void()>& func) = 0;

	//注册插件接口
	//virtual void setPluginInterface(Resafety::DarkStarStudio::ILayerManager* obj) = 0;
	//反注册插件接口
	//virtual Resafety::DarkStarStudio::ILayerManager* getPluginInterface() = 0;

	////设置资源视图的显隐
	//virtual void setResourceWidgetVisible(bool visible) = 0;

	////设置RenderWidget的大小；
	////virtual void resizeRenderWidget(uint32_t width, uint32_t height) = 0;

	//virtual void bindUpdateSceneView(const std::function<void(pafcore::Reference* reference)>& func) = 0;
	
};

}
}