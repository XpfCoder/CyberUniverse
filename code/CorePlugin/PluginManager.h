#pragma once
#include <QList>
#include "coreplugin_global.h"
#include "IPlugin.h"

namespace Resafety {
	namespace CyberUniverseStudio {

		//class ICore;
		class IPluginFactory;
		class IPlugin;
		class COREPLUGIN_EXPORT PluginManager
		{
			PluginManager();
			~PluginManager();
			PluginManager(const PluginManager&) = delete;
			PluginManager& operator=(const PluginManager&) = delete;

		public:
			static PluginManager* instance();

			void search();

			bool load();

			virtual IPlugin* getPlugin(const std::string& name);
			void addPlugin(QString& name, IPlugin* plugin);
		private:
			QMap<QString, IPluginFactory*> m_factorys;
			QMap<QString, IPlugin*> m_objects;
		};

	}
}
