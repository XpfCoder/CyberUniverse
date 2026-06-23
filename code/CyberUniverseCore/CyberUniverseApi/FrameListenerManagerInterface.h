#pragma once
#include <string>


namespace Resafety {
	namespace CyberUniverseStudio {
		class IFrameListener;
		class IFrameListenerManager
		{
		public:
			virtual ~IFrameListenerManager() {}
			virtual void registerFrameListener(IFrameListener* listener) = 0;
			virtual void registerFrameListener(const std::string& name, IFrameListener* listener) = 0;
			virtual void unregisterFrameListener(IFrameListener* listener) = 0;
			virtual void unregisterFrameListener(const std::string& name) = 0;
			virtual void frameMove(uint32_t interval) = 0;
			virtual void pauseRender(bool pause) = 0;
		public:
			bool m_stopRenderingEnabled{ false };
			int m_stopRenderingTime = 3600;
		};
		__declspec(dllexport) IFrameListenerManager* GetFrameListenerManager();
	}
}