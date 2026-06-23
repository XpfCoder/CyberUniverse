#pragma once
#include <QTreeView>
#include <QMenu>
#include "SceneCommonMenu.h"

namespace EngineCore { class Node; }; 
namespace EngineCore { class Scene; };

namespace Resafety {
	namespace CyberUniverseStudio {

		class ICore;

		class Q_DECL_EXPORT SceneView : public QTreeView
		{
			Q_OBJECT
		public:
			SceneView::SceneView(ICore* core, QWidget* parent = nullptr);
			void contextMenu(QModelIndex index);
			virtual void showMenu() {};

		private:
			std::vector<EngineCore::Node*> getSelectNode();
			virtual void selectedNodes(std::vector<EngineCore::Node* >& nodes);
			virtual void contextMenuEvent(QContextMenuEvent* event);
			EngineCore::Scene* getGraphicsScene();
		private:
			ICore* m_core{ nullptr };
			SceneCommonMenu* m_menu {nullptr};
			QAction* m_addAction{ nullptr };
			std::vector<EngineCore::Node*> m_selectNodes;
		protected slots:
			void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) override;
		signals:
			void selectChangle();
		};


	}
}