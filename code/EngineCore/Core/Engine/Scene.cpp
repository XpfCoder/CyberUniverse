#include  "Scene.h"

namespace EngineCore
{
	//RTTR_REGISTRATION
	//{
	//	rttr::registration::class_<Scene>("EngineCore::Scene")
	//		.constructor<>()
	//	;
	//;
	//}

	size_t Scene::getAddress()
	{
		return (size_t)this;
	}

	Node* Scene::getRootNode() const
	{
		return m_rootNode;
	}













}