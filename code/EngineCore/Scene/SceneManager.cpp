#include "SceneManager.h"
#include "../Core/engine/Engine.h"
//#include "Component/Common/RenderStates.h"
#include "Component/Camera/CameraManager.h"
#include "Component/Camera/CameraController.h"




namespace EngineCore
{
	void SceneManager::init()
	{
		m_pCameraController = new CameraController;

		CameraManager::getInstance().setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.330000f, 1.170000f, 0.0f),
			XMFLOAT3(-39.830292f, 30.397552f, -53.729988f)
		));

	}

	SceneManager::~SceneManager()
	{
		//for (auto iter = m_componets.begin(); iter != m_componets.end(); iter++)
		//{
		//	SAFE_DELETE_SET_NULL(iter->second);
		//}
		

	}

	void SceneManager::updateScene(float deltaTime)
	{

	}

	void SceneManager::drawScene()
	{	
		//sm_pSkyBoxComponent->draw();
		for (auto iter : m_componets)
		{
			iter.second->draw();
		}
	}
	 

	void SceneManager::setWireFrame(bool b)
	{
		//m_pd3dImmediateContext->RSSetState(b ? RenderStates::RSWireframe.Get() : RenderStates::RSNoCull.Get());
	}

	void SceneManager::addComponent(const std::string& componentType, const std::string& modelPath)
	{
		void* parameter[2];
		parameter[0] = m_pd3dDevice.Get();
		parameter[1] = m_pd3dImmediateContext.Get();

		


	}

	void SceneManager::addComponent(IComponent* component)
	{
		void* parameter[2];
		parameter[0] = m_pd3dDevice.Get();
		parameter[1] = m_pd3dImmediateContext.Get();

		m_componets.insert(std::make_pair(component->getComponetType(), component));


	}

	void SceneManager::deleteComponent(const std::string& uuid)
	{
	
			
	}

	void SceneManager::deleteAllComponent()
	{
	
	}

	void SceneManager::addNode(Node* node)
	{
		if (node)
		{
			m_nodes.push_back(node);
		}
	}

	void SceneManager::removeNode(Node* node)
	{
		auto it = std::find(m_nodes.begin(), m_nodes.end(), node);
		if (it != m_nodes.end())
		{
			m_nodes.erase(it);
		}
	}

	void SceneManager::clearNodes()
	{
		for (auto node : m_nodes)
		{
			delete node;
		}
		m_nodes.clear();
	}

	void SceneManager::setCameraMoveSpeed(float moveSpeed)
	{
		if (m_pCameraController)
		{
			m_pCameraController->setCameraMoveSpeed(moveSpeed);
		}
	}


	UINT SceneManager::getTriangleCount()
	{
		UINT triangleCount = 14;
		//for (auto& component : m_componets)
		//{
		//	triangleCount += component.second->getTriangleCount();
		//}
		return triangleCount;
	}


	std::vector<std::string> SceneManager::getAllComponetUuid()
	{
		std::vector<std::string> uuid;
		//for (auto& componet : m_componets)
		//{
		//	uuid.push_back(componet.first);
		//}

		return uuid;
	}

	//IComponent * SceneManager::getComponentByUuid(const std::string & uuid)
	//{
	//	auto iter = m_componets.find(uuid);
	//	if (iter != m_componets.end())
	//	{
	//		return iter->second;
	//	}
	//	return nullptr;
	//}

}

