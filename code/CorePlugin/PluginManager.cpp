#include "PluginManager.h"
//#include "IPlugin.h"
#include <QPluginLoader> 
#include <QApplication>
#include <QDir>
#include <QRegularExpression>
#include<QMenuBar>
#include<QToolBar>
#include <QtCore/QDebug>
#include <windows.h>
#include "CoreObject.h"
#include "../SARibbonBar\SARibbonBar.h"
#include "../SARibbonBar\SARibbonPannelItem.h"
#include "../SARibbonBar\SARibbonCategory.h"
#include "../SARibbonBar\SARibbonPannel.h"

using namespace Resafety::CyberUniverseStudio;

PluginManager::PluginManager()
{
}


PluginManager::~PluginManager()
{
}

PluginManager* PluginManager::instance()
{
	static PluginManager manager;
	return &manager;
}

void Resafety::CyberUniverseStudio::PluginManager::search()
{
	// 遍历目录
	QString appPath = QCoreApplication::applicationDirPath();
	QDir dir(appPath);
	dir.cd("CyberUniverseStudio");

	// 筛选文件，直接用正则表达式不好用
	QFileInfoList fileInfos = dir.entryInfoList(QStringList() << "*.dll", QDir::Files);
	QStringList pluginPaths;
	for (QFileInfo& fileInfo : fileInfos)
	{
		QString pluginPath = fileInfo.absoluteFilePath();
		if (pluginPath.contains("CorePlugin"))
		{
			continue;
		}

#ifdef _DEBUG
		QRegularExpression dllext("_d.dll");
#else
		QRegularExpression dllext("(?<!_d).dll");
#endif	

		if (!pluginPath.contains(dllext))
		{
			continue;
		}
		pluginPaths.push_back(pluginPath);
	}

#ifdef _DEBUG
	::SetDllDirectory((LPCWSTR)(appPath + "/plugins_d/").toStdString().c_str());
#else
	::SetDllDirectory((LPCWSTR)(appPath + "/plugins/").toStdString().c_str());
#endif

	// 发现插件
	m_factorys.clear();
	for (QString& pluginPath : pluginPaths)
	{
		QPluginLoader loader(pluginPath);
		IPluginFactory* factory = qobject_cast<IPluginFactory*>(loader.instance());
		if (!factory)
		{
			// error msg
			//return false;
			std::string err = loader.errorString().toStdString();
			qDebug() << loader.errorString();
			continue;
		}

		if (m_factorys.contains(factory->name()))
		{
			continue;
		}
		m_factorys[factory->name()] = factory;
	}
}


bool Resafety::CyberUniverseStudio::PluginManager::load()
{
	auto coreObject = CoreObject::instance();

	 //创建并加载插件对象，暂时默认全部加载
	m_objects.clear();
	for (auto factory : m_factorys)
	{
		IPlugin* plugin = factory->createPlugin();
		if (!plugin)
		{
			continue;
		}

		if (!plugin->load(coreObject))
		{
			continue;
		}
		m_objects.insert(factory->name(), plugin);
	}
	//coreObject->expendPluginAlter();  //加载插件时，将插件的风格转换为ribbon风格
	return true;
}
void PluginManager::addPlugin(QString& name, IPlugin* plugin)
{
	if (!m_objects.contains(name))
	{
		m_objects.insert(name, plugin);
	}
}
IPlugin* PluginManager::getPlugin(const std::string& name)
{
	IPlugin* p = nullptr;
	//std::string dummyName(name);
	QString qName = QString::fromStdString(name);
	if (!m_objects.contains(qName))
	{
		////强制加载插件
		//doLoadPlugin(name);
		////强制加载插件依然可能失败，因为插件可能根本不存在，或者插件存在错误
		//it = m_dynLibs.find(dummyName);
		return NULL;
	}

	return m_objects[qName];
}