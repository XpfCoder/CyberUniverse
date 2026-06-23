#pragma once

//#include "../CorePlugin/IPlugin.h"
#include "../Core/Base/GameTimer.h"
#include "../Core/Engine/Engine.h"

namespace EngineCore
{
	class __declspec(dllexport) EngineCore//:public Resafety::DarkStarStudio::IPlugin
	{
	public:
		EngineCore();
		~EngineCore();

		static EngineCore* GetInstance();
		//virtual bool load(Resafety::DarkStarStudio::ICore* core) { return false; };
		void initEngine3D(HWND hMainWnd, UINT windowWidth, UINT windowHeight);//传入主渲染窗口句柄，初始化3D;
		void UpdateScene(float dt);
		void onKeyPress(const Keys& key);
		void onKeyRelease(const Keys& key);
		void onMousePress(const MouseState& mouseState);
		void onMouseRelease(const MouseState& mouseState);
		void onMouseMove(const MouseState& mouseState);
		void onResize(unsigned short width, unsigned short height);
		void MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		float getGameInval();
		//std::unique_ptr<DirectX::Keyboard>& getKeyboard();
		//std::shared_ptr<Camera> getCamera();
		Engine* getEngineCore();

	private:
		Engine* m_Engine{ nullptr };
		GameTimer* m_gameTimer{ nullptr };
		//std::unique_ptr <DirectX::Keyboard> m_keyboard{ nullptr };
		//std::unique_ptr<DirectX::Mouse> m_pMouse{ nullptr };						// 鼠标

	};
}