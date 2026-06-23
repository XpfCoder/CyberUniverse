#pragma once
/************************************
Copyright:北京睿呈时代信息科技有限公司
Author: lihongchao
Date:2020/09/09 17:21
Description: CyberUniverseStudio插件抽象接口
************************************/
#include <QObject>
#include <QString>
#include <QtPlugin>

namespace Resafety {
	namespace CyberUniverseStudio {

		class ICore;
		class IPlugin
		{
		public:
			virtual bool load(ICore* core) = 0;
			virtual bool pluginHandle(const std::string& jsonStrs) { return true; };
		};

		class IPluginFactory
		{
		public:
			virtual IPlugin* createPlugin() = 0;

			virtual QString name() const = 0;
			virtual QString version() const = 0;
		};

	}
}

Q_DECLARE_INTERFACE(Resafety::CyberUniverseStudio::IPluginFactory, "CyberUniverseStudio.IPluginFactory")

#define BEGIN_DEEPWORLDEDITOR  namespace Resafety { \
namespace CyberUniverseStudio {

#define END_DEEPWORLDEDITOR  } }