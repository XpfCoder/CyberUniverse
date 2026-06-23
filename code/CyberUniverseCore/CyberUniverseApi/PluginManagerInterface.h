#pragma once
#include <string>

class IPlugin;
namespace Resafety {
	namespace CyberUniverseStudio {

		class IPluginManager
		{
		public:
			virtual void loadPlugin(const std::string& pluginPath) = 0;
			virtual void unloadPlugin(const std::string& name) = 0;
			virtual IPlugin* getPlugin(const std::string& name) = 0;
			virtual int totalPluginNum() const = 0;
			virtual int loadedPluginNum() const = 0;
			virtual bool loadFinished() const = 0;
		};

		__declspec(dllexport) IPluginManager* GetPluginManager();

	}
}
