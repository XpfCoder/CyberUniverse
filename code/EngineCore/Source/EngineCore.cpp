#include "EngineCore.h"
#include "../Scene/Component/Effect/BoxComponent.h"
#include "../Scene/Component/Effect/SkyComponent.h"
#include "../Scene/Component/Effect/GroundComponent.h"
#include "../../Scene/SceneManager.h"
#include "../Asset/AssetManager.h"
#include <iostream>
#include <fstream>
#include "../Scene/Component/Effect/BillboardConponent.h"
namespace EngineCore
{

	EngineCore* EngineCore::GetInstance()
	{
		static EngineCore* s_instance = nullptr;
		if (s_instance == nullptr)
		{
			s_instance = new EngineCore();
		}
		return s_instance;
	}


	EngineCore::EngineCore()
	{
		m_Engine = &Engine::getInstance();
		m_gameTimer = new GameTimer();
	}
	EngineCore::~EngineCore()
	{
		delete m_Engine;
		m_Engine = nullptr;
	}

	static Node* createNodeForComponent(IComponent* comp, const std::string& name)
	{
		Node* node = new Node();
		node->setName(name);
		node->addComponent(comp);
		comp->setOwnerNode(node);
		SceneManager::getInstance().addNode(node);
		return node;
	}

	void EngineCore::initEngine3D(HWND hMainWnd, UINT windowWidth, UINT windowHeight)
	{
		m_Engine->initialize(hMainWnd, windowWidth, windowHeight);
		AssetManager::getInstance().initialize(m_Engine->m_pd3dDevice, m_Engine->m_pd3dImmediateContext);

		IComponent* box = new BoxComponent(m_Engine->m_pd3dDevice, m_Engine->m_pd3dImmediateContext);
		SceneManager::getInstance().addComponent(box);
		createNodeForComponent(box, "Box");

		IComponent* sky = new SkyComponent(m_Engine->m_pd3dDevice, m_Engine->m_pd3dImmediateContext);
		SceneManager::getInstance().addComponent(sky);
		createNodeForComponent(sky, "Sky");

		IComponent* ground = new GroundComponent(m_Engine->m_pd3dDevice, m_Engine->m_pd3dImmediateContext);
		SceneManager::getInstance().addComponent(ground);
		createNodeForComponent(ground, "Ground");

		IComponent* billboard = new BillboardConponent(m_Engine->m_pd3dDevice, m_Engine->m_pd3dImmediateContext);
		SceneManager::getInstance().addComponent(billboard);
		createNodeForComponent(billboard, "Billboard");
	}

	void  EngineCore::UpdateScene(float dt)
	{
		m_Engine->updateScene(dt);
		m_Engine->drawScene();

		m_gameTimer->Tick();

	}

	float EngineCore::getGameInval()
	{
		if (m_gameTimer)
			return m_gameTimer->DeltaTime();
		return 0;
	}

	void EngineCore::onKeyPress(const Keys& key)
	{
		InputEventManager::getInstance().onKeyPress(key);
	}

	void EngineCore::onKeyRelease(const Keys& key)
	{
		InputEventManager::getInstance().onKeyRelease(key);
	}

	void EngineCore::onMousePress(const MouseState& mouseState)
	{ 
		InputEventManager::getInstance().onMousePress(mouseState);
	}

	void EngineCore::onMouseRelease(const MouseState& mouseState)
	{ 
		InputEventManager::getInstance().onMouseRelease(mouseState);
	}

	void EngineCore::onMouseMove(const MouseState& mouseState)
	{ 
		InputEventManager::getInstance().onMouseMove(mouseState);
	}

	//std::unique_ptr<DirectX::Keyboard>& EngineCore::getKeyboard()
	//{
	//	return m_Engine->getKeyboard();
	//}

	void EngineCore::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//m_Engine->MsgProc(hwnd, msg, wParam, lParam);
	}

	//std::shared_ptr<Camera> EngineCore::getCamera()
	//{
	//	return m_Engine->getCamera();
	//}

	Engine* EngineCore::getEngineCore()
	{
		return m_Engine;
	}


	void EngineCore::onResize(unsigned short width, unsigned short height)
	{
		m_Engine->onResize(width, height);
	}



}