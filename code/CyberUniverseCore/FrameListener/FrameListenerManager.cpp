#include "FrameListenerManager.h"
#include <thread>
#include "../CyberUniverseApi/FrameListenerInterface.h"
//#include "../CyberUniverseApi/PickEventManagerInterface.h"
//#include "paf/pafcore/Utility.h"
//#include "DeepEyeCore/Engine/Engine.h"
#include "../CyberUniverseApi/InputEventManagerInterface.h"

namespace Resafety {
	namespace CyberUniverseStudio {
		FrameListenerManager::FrameListenerManager()
		{

		}

		FrameListenerManager::~FrameListenerManager()
		{
			m_listeners.clear();
			m_namedListeners.clear();
			m_removedListeners.clear();
		}

		void FrameListenerManager::registerFrameListener(const std::string& name, IFrameListener* listener)
		{
			//不进行重复检查，替换之前的listener
			m_namedListeners[name] = listener;
			registerFrameListener(listener);
		}

		void FrameListenerManager::registerFrameListener(IFrameListener* listener)
		{
			m_removedListeners.erase(listener);
			m_listeners.push_front(listener);
		}

		void FrameListenerManager::unregisterFrameListener(IFrameListener* listener)
		{
			m_removedListeners.insert(listener);
		}

		void FrameListenerManager::unregisterFrameListener(const std::string& name)
		{
			auto it = m_namedListeners.find(name);
			if (it != m_namedListeners.end())
			{
				unregisterFrameListener(it->second);
				m_namedListeners.erase(it);
			}
		}

		void FrameListenerManager::frameMove(uint32_t deltaTime)
		{
			if (m_pauseRender)
			{
				std::chrono::milliseconds timespan(16);
				std::this_thread::sleep_for(timespan);
				return;
			}

		//	if (m_stopRenderingEnabled)
		//	{
		//		if ((Resafety::DeepEye::Platform::GetMillisecond() - GetInputEventManager()->getLastInputEventTime()) > m_stopRenderingTime * 1000)
		//		{
		//			std::chrono::milliseconds timespan(16);
		//			std::this_thread::sleep_for(timespan);
		//			return;
		//		}
		//	}

		//	Resafety::DeepEye::Engine::GetInstance()->update();
		//	syncListener();
		//	for (auto listener : m_listeners)
		//	{
		//		listener->frameMove(deltaTime);
		//	}
		//	Resafety::CyberUniverseStudio::GetPickEventManager()->update();
		}

		void FrameListenerManager::pauseRender(bool pause)
		{
			m_pauseRender = pause;
		}

		void FrameListenerManager::syncListener()
		{
			if (m_removedListeners.empty())
			{
				return;
			}
			for (auto e : m_removedListeners)
			{
				m_listeners.remove(e);
			}
			m_removedListeners.clear();
		}
	}
}