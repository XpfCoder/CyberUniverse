#include "SceneEditPlugin.h"
#include "SceneEditDockWidget.h"
#include "../CorePlugin/ICore.h"
namespace Resafety {
	namespace CyberUniverseStudio {

		bool SceneEditPlugin::load(ICore* core)
		{
			auto dockWidget = new SceneEditDockWidget(core, QObject::tr(u8"³¡¾°±à¼­ÊÓÍ¼"));//³¡¾°±à¼­ÊÓÍ¼

			dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
			core->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
			return true;
		}


	}
}