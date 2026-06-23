#include "../CorePlugin/IPlugin.h"
#include <string>
namespace Resafety {
	namespace CyberUniverseStudio {
		class __declspec(dllexport) InitKernel
		{
		public:
			virtual size_t getAddress();


			static InitKernel* GetInstance();

			bool init(void* mainWnd, const std::string& assetsDir, const std::string& solutionName);
			IPlugin* getPlugin(std::string& name)const;
			void unloadPlugin(std::string& name);
			std::string& getExePath()const;

			std::string& getSysConfigPath()const;
			std::string& getSolutionPath()const;

		};
	}
}