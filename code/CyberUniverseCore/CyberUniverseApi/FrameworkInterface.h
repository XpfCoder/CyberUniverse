#pragma once
#include <string>

typedef bool (*POST)(const char* str);


namespace Resafety {
	namespace CyberUniverseStudio {

		class GeoScene;

		struct EngineSettingConfig
		{
			uint32_t dataLoadingThreadCount{ 1 };
			uint32_t graphicsLoadingThreadCount{ 1 };
			uint32_t graphicsRenderThreadCount{ 1 };
			uint32_t pickLoadingThreadCount{ 1 };
			uint32_t miscAssetLoadingThreadCount{ 1 };
			bool dataAsyncDeleting{ false };
			bool graphicsAssetAsyncDeleting{ false };
			bool miscAssetAsyncDeleting{ false };
			bool pickAssetAsyncDeleting{ false };
		};

		struct FrameworkConfig
		{
			std::string exePath;
			std::string solutionPath;
			std::string solutionName;
			int width{ 1920 };
			int height{ 1080 };
			bool isPpapi{ false };
			bool isChrome{ false };
			bool isCloudRender{ false };
			bool isClusterMaster{ false };
			bool showClusterMaster{ false };
			void* mainWnd{ nullptr };
			POST myPostMessage{ nullptr };
			std::string resMode;
			std::string m_remotePath;
			EngineSettingConfig engineSetting;
			int planeMode{ 0 };
			double rangeEast = -1.0f;
			double rangeWest = -1.0f;
			double rangeNorth = -1.0f;
			double rangeSouth = -1.0f;
			double mapscale = -1.0f;
			int encryptionMode = 0;
		};

		class IFramework
		{
		public:
			virtual void init(const FrameworkConfig& configInfo, bool bloadNetResource, bool useRclone) = 0;
			virtual GeoScene* getEarthScene() const = 0;
		};

		__declspec(dllexport) IFramework* GetFramework();
	}
}