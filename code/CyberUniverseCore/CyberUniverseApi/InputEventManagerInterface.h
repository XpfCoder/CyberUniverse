#pragma once
#include <string>
/*!
* @brief 事件管理器。负责统一管理鼠标键盘事件。目前没有提供事件优先级
*
* @author subai
* @date 2019/11/23
*/
namespace Resafety {
	namespace CyberUniverseStudio {
		class IInputEvent;
		class IInputEventManager
		{
		public:
			virtual ~IInputEventManager() = default;
			virtual void registerInputEvent(IInputEvent* inputEvent) = 0;
			virtual void registerInputEvent(const std::string& name, IInputEvent* inputEvent) = 0;
			virtual void unregisterInputEvent(IInputEvent* inputEvent) = 0;
			virtual void unregisterInputEvent(const std::string& name) = 0;
			virtual void onMouseMove(uint32_t nFlags, int x, int y) = 0;
			virtual void onMouseWheel(uint32_t nFlags, short zDelta, int x, int y) = 0;
			virtual void onLButtonDblClk(uint32_t nFlags, int x, int y) = 0;
			virtual void onMButtonDblClk(uint32_t nFlags, int x, int y) = 0;
			virtual void onRButtonDblClk(uint32_t nFlags, int x, int y) = 0;
			virtual void onLButtonDown(uint32_t nFlags, int x, int y) = 0;
			virtual void onMButtonDown(uint32_t nFlags, int x, int y) = 0;
			virtual void onRButtonDown(uint32_t nFlags, int x, int y) = 0;
			virtual void onLButtonUp(uint32_t nFlags, int x, int y) = 0;
			virtual void onMButtonUp(uint32_t nFlags, int x, int y) = 0;
			virtual void onRButtonUp(uint32_t nFlags, int x, int y) = 0;
			virtual void onSize(uint32_t nType, int cx, int cy) = 0;
			virtual void onTouchBegin(int touchCount, float* x, float* y) = 0;
			virtual void onTouchUpdate(int touchCount, float* x, float* y) = 0;
			virtual void onTouchEnd(int touchCount, float* x, float* y) = 0;
			virtual void onTouchCancle(int touchCount, float* x, float* y) = 0;
			virtual void onLostCapture() = 0;
			virtual void onLostFocus() = 0;
			virtual void onKeyDown() = 0;
		public:
			virtual uint32_t getLastInputEventTime() = 0;
			virtual void updateLastInputEventTime() = 0;
		};
		__declspec(dllexport) IInputEventManager* GetInputEventManager();
	}
}
