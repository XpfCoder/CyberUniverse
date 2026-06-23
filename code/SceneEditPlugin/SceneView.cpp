#include "SceneView.h"
#include <QContextMenuEvent>
#include <QtWidgets/QApplication.h>
#include <QtGui/QClipboard>
#include "../CyberUniverseGeo/Scene/GeoNode.h"
#include "SceneTreeModel.h"
#include "../CorePlugin/ICore.h"
#include "TreeItem.h"
#include "../EngineCore/Core/Engine/Component.h"
#include "../EngineCore/Core/Engine/Node.h"
namespace Resafety {
	namespace CyberUniverseStudio {


		SceneView::SceneView(ICore* core, QWidget* parent /*= nullptr*/)
			:m_core(core)
		{
			m_menu = new SceneCommonMenu(this);
			m_menu->addCommonAction();
			m_addAction = m_menu->action(Menu_Add);
		}

		void SceneView::contextMenuEvent(QContextMenuEvent* event)
		{
			QPoint cursorPos = event->pos();
			QModelIndex index = this->indexAt(cursorPos);
			contextMenu(index);
		}

		void SceneView::contextMenu(QModelIndex index)
		{
			int f = Menu_Add;

			if (index.isValid())
			{
				f |= Menu_Delete;
			}

			if (index.isValid())
			{
				f |= Menu_Delete | Menu_Save;
			}

			m_menu->enabledAction(f);
			m_menu->exec(QCursor::pos());
		}


		void SceneView::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
		{
			std::vector<EngineCore::Node*> nodes = getSelectNode();
			auto scene = getGraphicsScene();

			m_core->nodeSelectChangle(scene, nodes);
			emit selectChangle();
		}

		std::vector<EngineCore::Node*> SceneView::getSelectNode()
		{
			m_selectNodes.clear();
			auto indexs = this->selectedIndexes();
			for (auto& idx : indexs)
			{
				TreeItem* item = (TreeItem*)idx.internalPointer();
				if (!item || !item->ptr()) continue;

				EngineCore::Node* node = static_cast<EngineCore::Node*>(item->ptr());
				if (node)
				{
					m_selectNodes.push_back(node);
				}
			}
			return m_selectNodes;
		}

		void SceneView::selectedNodes(std::vector<EngineCore::Node* >& nodes)
		{
			if (SceneTreeModel* sceneModel = qobject_cast<SceneTreeModel*>(this->model()))
			{
				if (nodes.size())
				{
					this->selectionModel()->select(this->currentIndex(), QItemSelectionModel::Clear | QItemSelectionModel::Deselect);
					QModelIndex selIndex;
					for (auto node : nodes)
					{
						//QModelIndex index = sceneModel->getNodeIndex(node);
						//selIndex = index;
						//this->selectionModel()->select(index, QItemSelectionModel::Select);
					}
					this->selectionModel()->setCurrentIndex(selIndex, QItemSelectionModel::SelectCurrent);
				}
			}
		}

		EngineCore::Scene* SceneView::getGraphicsScene()
		{
			if (SceneTreeModel* sceneModel = qobject_cast<SceneTreeModel*>(this->model()))
			{
				return sceneModel->getScene();
			}
			return nullptr;
		}
	}
}