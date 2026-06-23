#include "GeoNode.h"
#include "Utility.h"
namespace EngineCore
{
		class GeoScene;
		GeoNode::GeoNode()
		{
			m_uuid = GenerateGuid();
			m_releaseMemoryUuid = m_uuid;
			//GeoNodeManager::GetInstance()->addGeoNode(m_uuid, this);
		}

		//RTTR_REGISTRATION
		//{
		//	rttr::registration::class_<GeoNode>("EngineCore::GeoNode")
		//		.constructor<>()
		//		.property("uuid", &GeoNode::get_uuid, &GeoNode::set_uuid)
		//		;

		//;
		//}


		GeoNode::~GeoNode()
		{
			//GeoNodeManager::GetInstance()->removeGeoNode(m_releaseMemoryUuid);
		}

		GeoNode* GeoNode::New()
		{
			return new GeoNode();
		}
		size_t GeoNode::getAddress()
		{
			return (size_t)this;
		}

		//void GeoNode::pushBack_nodes(GeoNode* node)
		//{
		//	node->addToParent(this);
		//}


		GeoScene* GeoNode::getScene()
		{
			return reinterpret_cast<GeoScene*>(m_scene);
		}

	
}

