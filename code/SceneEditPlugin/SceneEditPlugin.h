#pragma once
#include "../CorePlugin/IPlugin.h"
#include "sceneeditplugin_global.h"

namespace Resafety {
	namespace CyberUniverseStudio {

		class SCENEEDITPLUGIN_EXPORT SceneEditPlugin :public QObject, public IPlugin
		{
			Q_OBJECT
		public:
			bool load(ICore* core) override;
		};


		class SceneEditPluginFactory : public QObject, public IPluginFactory
		{
			Q_OBJECT
				Q_INTERFACES(Resafety::CyberUniverseStudio::IPluginFactory)
				Q_PLUGIN_METADATA(IID "CyberUniverseStudio.SceneEditPlugin")

		public:
			virtual IPlugin* createPlugin()
			{
				return new SceneEditPlugin;
			}

			QString name() const override { return "SceneEditPlugin"; }
			QString version() const override { return "1.0.0"; }
		};




	}
}