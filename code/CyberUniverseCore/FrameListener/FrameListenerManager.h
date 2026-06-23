#pragma once
#include "DeepEyeCore/Engine/Component.h"
#include "../CyberUniverseApi/FrameListenerManagerInterface.h"
#include <forward_list>
#include <string>
#include <map>
#include <set>
/*!
 * @brief 帧监听事件的管理器，负责统一调用所有的帧监听接口。
 *
 * @detail 该类没有导出，也没有接口类，外部模块无法调用。外部模块需要调用KernelInterface中的frameMove触发帧监听事件
 *
 */
namespace Resafety {
	namespace CyberUniverseStudio {
		class FrameListenerManager : public IFrameListenerManager
		{
		public:
			FrameListenerManager();
			virtual ~FrameListenerManager();
		public:
			virtual void registerFrameListener(const std::string& name, IFrameListener* listener) override;
			virtual void registerFrameListener(IFrameListener* listener) override;
			virtual void unregisterFrameListener(IFrameListener* listener) override;
			virtual void unregisterFrameListener(const std::string& name) override;
			virtual void frameMove(uint32_t deltaTime) override;
			virtual void pauseRender(bool pause) override;
		private:
			void syncListener();
		private:
			std::forward_list<IFrameListener*> m_listeners;
			//带有名字的listener，以便根据名字进行反注册，便于lua、js脚本反注册。由用户保证名字的唯一性。
			//依然保留直接通过指针进行注册和反注册的方式，便于C++使用
			std::map<std::string, IFrameListener*> m_namedListeners;
			std::set<IFrameListener*> m_removedListeners;
			bool m_pauseRender{ false };


		};
	}
}