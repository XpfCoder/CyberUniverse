#ifndef CYBER_SCENEMANAGER
#define CYBER_SCENEMANAGER



#include <vector>
#include "../Core/base/SingletonInterface.h"
#include "../Core/base/ManagerInterface.h"
#include <string>
#include "../Core/Engine/Component.h"
#include "../Core/Engine/Node.h"
#include <map>
//#include "Light/LightManager.h"

namespace EngineCore
{
	class CameraController;


	class __declspec(dllexport) SceneManager : public ISingleton<SceneManager>, public IManager
	{
	public:
		virtual ~SceneManager();
	public:
		virtual void init() override;
		void updateScene(float deltaTime);
		void drawScene();
	public:

		void setWireFrame(bool b);
		void addComponent(const std::string& componentType, const std::string& modelPath = "");
		void addComponent(IComponent* component);
		void deleteComponent(const std::string& uuid);
		void deleteAllComponent();
		void setCameraMoveSpeed(float moveSpeed);
		UINT getTriangleCount();

		// Node management
		void addNode(Node* node);
		void removeNode(Node* node);
		const std::vector<Node*>& getNodes() const { return m_nodes; }
		void clearNodes();

		std::vector<std::string> getAllComponetUuid(); 

	private:
		CameraController* m_pCameraController{ nullptr };
		std::map<std::string, IComponent*> m_componets;
		std::vector<Node*> m_nodes;
	};
}

#endif // !CYBER_SCENEMANAGER