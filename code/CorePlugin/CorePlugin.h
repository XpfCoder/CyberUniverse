/************************************
Copyright:北京睿呈时代信息科技有限公司
Author: lihongchao
Date:2020/09/09 17:29
Description: 核心插件类

1、插件框架及插件管理。
2、基于QMainWindow的界面扩展支持。
************************************/
#pragma once
#include "coreplugin_global.h"
#include "IPlugin.h"
//#include "../external\Engine\deepeye\src\DeepEyeExt\Log\LogCategory.h"
//#include <fstream>

namespace Resafety {
	namespace CyberUniverseStudio {

		class CorePlugin : public IPlugin
		{
		public:
			bool load(ICore* core); //override;
			bool pluginHandle(const std::string& jsonStrs);
		};

		class CorePluginFactory : public QObject, public IPluginFactory
		{
			Q_OBJECT
				Q_INTERFACES(Resafety::CyberUniverseStudio::IPluginFactory)
				Q_PLUGIN_METADATA(IID "KernelStudio.CorePlugin")

		public:
			virtual IPlugin *createPlugin()
			{
				return new CorePlugin;
			}

			QString name() const override { return "CorePlugin"; }
			QString version() const override { return "1.0.0"; }
		};

	}
}

