#pragma once
#include "../CyberUniverseApi/PluginManagerInterface.h"
#include <map>
#include <string>
namespace Resafety
{
	namespace DeepEye
	{
		class GeoNode;
	}
}
/*!
 * @brief 各个图层根节点的生成器。
 *
 *@detail 目前场景的组织方式为，根节点为地球节点，下面挂五个节点，分别为:矢量图层节点(VectorLayer)、栅格图层节点(GridLayer)、
 离散模型层节点(Discrete3DLayer)、层次规则化模型层节点(Standard3DLayer)、运行时效果图层(RuntimeEffect)
 *
 * @author subai
 * @date 2020/8/15
 */

#define MODEL u8"模型"
#define EFFECT u8"效果"
#define BUILDING u8"房屋面"
namespace Resafety {
	namespace CyberUniverseStudio {
		class __declspec(dllexport) RootNodeProvider
		{
		public:
			static RootNodeProvider* GetInstance();
		public:
			Resafety::DeepEye::GeoNode* getRootNode(const char* nodeName, bool editableInEditor = false);
		private:
#pragma warning(push)
#pragma warning(disable:4251)
			std::map<std::string, Resafety::DeepEye::GeoNode*> m_rootNodes;
#pragma warning(pop)
		};
	}
}