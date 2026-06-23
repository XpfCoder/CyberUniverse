#pragma once
#include <QDockWidget>
#include <QSplitter>
namespace Resafety {
	namespace CyberUniverseStudio {

		class ICore;

		class SceneEditDockWidget : public QDockWidget
		{
			Q_OBJECT
		public:
			SceneEditDockWidget(ICore* core, const QString& title, QWidget* parent = nullptr);
			~SceneEditDockWidget();

		//protected slots:
		//	void onToolButtonClicked(bool val);
		//	void onParkLayerEditorButtonClicked();

		protected:
			//ScenePickHandler* m_pickHandler{ nullptr };
			//ParkLayerTreeWidget* m_parkLayerTree{ nullptr };
			QSplitter* m_frameSpliter{ nullptr };
			bool m_parkClicked{ false };
		};


	}
}