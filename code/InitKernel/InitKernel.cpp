#include "InitKernel.h"

namespace Resafety {
	namespace CyberUniverseStudio {


		InitKernel* InitKernel::GetInstance()
		{
			static InitKernel* s_instance = nullptr;
			if (s_instance == nullptr)
			{
				s_instance = new InitKernel();
			}
			return s_instance;
		}



		bool InitKernel::init(void* mainWnd, const std::string& assetsDir, const std::string& solutionName)
		{
			return m_impl->init(mainWnd, assetsDir, solutionName);
		}

		IPlugin* InitKernel::getPlugin(std::string& name) const
		{
			PAF_ASSERT(Resafety::DeepWorld::GetPluginManager() != nullptr);
			return Resafety::DeepWorld::GetPluginManager()->getPlugin(name.c_str());
		}

		void InitKernel::unloadPlugin(std::string& name)
		{
			PAF_ASSERT(Resafety::DeepWorld::GetPluginManager() != nullptr);
			return Resafety::DeepWorld::GetPluginManager()->unloadPlugin(name.c_str());
		}

		ISysConfiger* InitKernel::getSysConfiger()
		{

			return m_impl->m_sysConfiger;
		}

		GeoScene* InitKernel::getEarthScene() const
		{
			return Resafety::DeepWorld::GetFramework()->getEarthScene();
		}

		std::string& InitKernel::getExePath() const
		{
			return m_impl->m_env.exePath.c_str();
		}

		std::string& InitKernel::getSysConfigPath() const
		{

			return m_impl->m_solutionPath.c_str();
		}








	}
}