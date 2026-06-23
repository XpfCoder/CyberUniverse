#ifndef CYBER_CAMERACHANGEDMANAGER
#define CYBER_CAMERACHANGEDMANAGER


#include "../base/SingletonInterface.h"
#include <vector>

namespace EngineCore
{
	class CameraMoveEvent
	{
	public:
		virtual void onCameraMove() = 0;
	};

	class CameraFrustumChangedEvent
	{
	public:
		virtual void onCameraFrustumChanged() = 0;
	};

	class CameraChangedManager : public ISingleton<CameraChangedManager>
	{
	public:
		void registerCameraMoveEvent(CameraMoveEvent* cameraMoveEvent);
		void unRegisterCameraMoveEvent(CameraMoveEvent* cameraMoveEvent);
		void onCameraMove();

		void registerCameraFrustumChangedEvent(CameraFrustumChangedEvent* cameraFrustumChangedEvent);
		void unRegisterCameraFrustumChangedEvent(CameraFrustumChangedEvent* cameraFrustumChangedEvent);
		void onCameraFrustumChanged();
	private:
		std::vector<CameraMoveEvent*> m_cameraMoveEvents;
		std::vector<CameraFrustumChangedEvent*> m_cameraFrustumChangedEvent;
	};

}


#endif // !CYBER_CAMERACHANGEDMANAGER

