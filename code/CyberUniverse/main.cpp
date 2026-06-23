#include <QLibrary>
#include <QPluginLoader> 
#include <filesystem>
#include <QtCore/QTranslator>
#include "../CorePlugin/IPlugin.h"
#include <QtWidgets/QApplication>
#include <Qfile>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//QApplication::setStyle(QStyleFactory::create("Fusion"));


	// 发现、创建、加载核心插件
	QString appPath = QCoreApplication::applicationDirPath();

#ifdef _DEBUG
	QString dllext = "_d.dll";
#else
	QString dllext = ".dll";
#endif
	QString pluginFile = appPath + "/CyberUniverseStudio/CorePlugin" + dllext;
	QPluginLoader loader(pluginFile);
	//QPluginLoader loader("F:\\Direct3D11Test\\CyberUniverseStudio\\bin_64\\CyberUniverseStudio\\CorePlugin_d.dll");
	loader.instance();
	auto factory = qobject_cast<Resafety::CyberUniverseStudio::IPluginFactory*>(loader.instance());
	if (!factory)
	{
		// error msg
		return false;
	}

	auto plugin = factory->createPlugin();
	if (!plugin)
	{
		// error msg
		return false;
	}

	// 加载核心插件必定成功
	plugin->load(nullptr);

	return a.exec();
}
