#pragma once
#include "CyberUniverseApi/FrameworkInterface.h"
#include "HotKey/HotKeyManager.h"
namespace Resafety {
	namespace CyberUniverseStudio {


		class Framework : public IFramework
		{

		public:
			Framework();
			virtual ~Framework();
		public:
			virtual void init(const FrameworkConfig& configInfo, bool bloadNetResource, bool useRclone) override;
			virtual GeoScene* getEarthScene() const override;
			
			//以前的earthNode，所有地球上的物体都需要添加到该场景下
			GeoScene* m_earthScene{ nullptr };

			void* m_renderWnd{ nullptr };


		public:
			//LogManager* m_logMgr{ nullptr };
			ILogInterface* m_logMgr{ nullptr };
			HotKeyManager* m_hotKeyMgr{ nullptr };

		};









	}
}
