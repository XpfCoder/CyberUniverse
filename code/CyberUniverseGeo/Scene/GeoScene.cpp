#include "GeoNode.h"
#include "GeoScene.h"

namespace EngineCore
{
	RTTR_REGISTRATION
	{
		rttr::registration::class_<Node>("EngineCore::Node")
			.constructor<>()
			.property("name", &Node::get_name, &Node::set_name)
			;

	;
	}

		GeoScene::GeoScene()
		{
;
		}

		GeoScene::~GeoScene()
		{

		}


		size_t GeoScene::getAddress()
		{
			return (size_t)this;
		}

		//GeoNode* GeoScene::getFirstTopNode() const
		//{
		//	return static_cast<GeoNode*>(Scene::getFirstTopNode());
		//}

		//GeoNode* GeoScene::getLastTopNode() const
		//{
		//	return static_cast<GeoNode*>(Scene::getLastTopNode());
		//}

	
}

