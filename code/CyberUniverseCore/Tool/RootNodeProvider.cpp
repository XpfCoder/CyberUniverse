#include "RootNodeProvider.h"
#include "DeepEyeGeo/Scene/GeoNode.h"
#include "../CyberUniverseApi/FrameworkInterface.h"

namespace Resafety {
	namespace CyberUniverseStudio {
		RootNodeProvider* RootNodeProvider::GetInstance()
		{
			static RootNodeProvider* s_instance = nullptr;
			if (s_instance == nullptr)
			{
				s_instance = new RootNodeProvider;
			}
			return s_instance;
		}

		Resafety::DeepEye::GeoNode* RootNodeProvider::getRootNode(const char* nodeName, bool editableInEditor /*= false*/)
		{
			Resafety::DeepEye::GeoNode* rootNode = nullptr;
			std::string tmp(nodeName);
			auto it = m_rootNodes.find(nodeName);
			if (it == m_rootNodes.end())
			{
				rootNode = Resafety::DeepEye::GeoNode::New();
				rootNode->setEditable(editableInEditor);
				std::string tmp(nodeName);
				if (tmp == "SortbleLayer" || tmp == "RuntimeEffect")
					rootNode->setEditable(true);
				rootNode->set_name(nodeName);
				//rootNode->addToSceneRoot(Resafety::DeepWorld::GetFramework()->getEarthScene());
				m_rootNodes[nodeName] = rootNode;
			}
			else
			{
				rootNode = it->second;
				SafeAddRef(rootNode);
			}
			return rootNode;
		}

	}
}

