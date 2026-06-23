#ifndef CYBER_ENGINE
#define CYBER_ENGINE

#include <d3d11_1.h>
#include "../Base/SingletonInterface.h"
#include <wrl/client.h>
#include "../Event/InputEventManager.h"
#include "../Event/FrameMoveEventManager.h"
#include <map>
//#include "../../Scene/SceneManager.h"
#include "../../Asset/DDSTextureLoader.h"
#include "../../Asset/WICTextureLoader.h"
#include "../Base/d3dUtil.h"

namespace EngineCore
{
	using namespace Microsoft::WRL;
	class Engine :public ISingleton<Engine>
	{
		
	public:
		Engine();
		~Engine();
	public:
		void initialize(HWND hInstance, UINT windowWidth, UINT windowHeight);
		void updateScene(float deltaTime);
		void drawScene();
		void onResize(UINT windowWidth, UINT windowHeight);
	public:
		void onKeyPress(const Keys& key) { InputEventManager::getInstance().onKeyPress(key); if (!m_isKeyDown[key]) m_isKeyDown[key] = true; }
		void onKeyRelease(const Keys& key) { InputEventManager::getInstance().onKeyRelease(key); if (m_isKeyDown[key])m_isKeyDown[key] = false; }
		void onMousePress(const MouseState& mouseState) { InputEventManager::getInstance().onMousePress(mouseState); m_bIsMousePress[mouseState.mouseType] = true; }
		void onMouseRelease(const MouseState& mouseState) { InputEventManager::getInstance().onMouseRelease(mouseState); m_bIsMousePress[mouseState.mouseType] = false; }
		void onMouseMove(const MouseState& mouseState) { InputEventManager::getInstance().onMouseMove(mouseState); m_mousePos = mouseState.mousePos; }
		void onMouseWheelEvent(const MouseState& mouseState) { InputEventManager::getInstance().onMouseWheelEvent(mouseState); }
	public:
		ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
	private:
		HWND m_hInstance;
		UINT m_windowWidth;
		UINT m_windowHeight;

		UINT m_4xMsaaQuality;


		ComPtr<IDXGISwapChain> m_pSwapChain{ nullptr };

		ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer{ nullptr };
		ComPtr<ID3D11RenderTargetView> m_pRenderTargetView{ nullptr };
		ComPtr<ID3D11DepthStencilView> m_pDepthStencilView{ nullptr };

		D3D11_VIEWPORT m_ScreenViewport;

		MousePos m_mousePos;
		std::map<MouseType, bool> m_bIsMousePress;
		std::map<Keys, bool> m_isKeyDown;
	};
	
}












#endif // !CYBER_ENGINE


