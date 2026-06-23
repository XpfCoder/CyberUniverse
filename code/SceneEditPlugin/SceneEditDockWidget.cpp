#include "SceneEditDockWidget.h"
#include "SceneTreeModel.h"
#include "SceneView.h"
#include "TreeItem.h"
#include <QHeaderView>
#include <QTimer>
#include "../EngineCore/Scene/SceneManager.h"
#include "../EngineCore/Core/Engine/Node.h"
#include "../EngineCore/Core/Engine/Component.h"
namespace Resafety {
	namespace CyberUniverseStudio {

		SceneEditDockWidget::SceneEditDockWidget(ICore* core, const QString& title, QWidget* parent /*= nullptr*/)
			:QDockWidget(title, parent)
		{
			SceneView* sceneView = new SceneView(core);
			sceneView->setHeaderHidden(true);
			sceneView->setSelectionBehavior(QTreeView::SelectRows);
			sceneView->setSelectionMode(QTreeView::SingleSelection);
			sceneView->setFocusPolicy(Qt::NoFocus);
			sceneView->header()->setStretchLastSection(true);

			this->setWidget(sceneView);

			SceneTreeModel* model = new SceneTreeModel(sceneView);
			TreeItem* root = model->root();

			// Build tree from SceneManager nodes
			auto& nodes = EngineCore::SceneManager::getInstance().getNodes();
			for (auto node : nodes)
			{
				TreeItem* item = new TreeItem(root);
				item->setPtr(static_cast<void*>(node));
				root->addChild(item);
			}

			sceneView->setModel(model);

			// Periodically refresh tree
			QTimer* refreshTimer = new QTimer(this);
			connect(refreshTimer, &QTimer::timeout, [model]() {
				model->layoutChanged();
			});
			refreshTimer->start(3000);
		}

		SceneEditDockWidget::~SceneEditDockWidget()
		{
		}
	}
}
