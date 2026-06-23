#pragma once
#include <QAbstractItemModel>

namespace EngineCore { class Node; };
namespace EngineCore { class Scene; };

namespace Resafety {
	namespace CyberUniverseStudio {



        class TreeItem;

        class SceneTreeModel : public QAbstractItemModel
        {
            Q_OBJECT
        public:
            explicit SceneTreeModel(QObject* parent = nullptr);
            ~SceneTreeModel() override;

            TreeItem* root();

            QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
            QVariant data(const QModelIndex& index, int role) const override;
            QModelIndex index(int row, int column, const QModelIndex& parent) const override;
            QModelIndex parent(const QModelIndex& index) const override;
            int rowCount(const QModelIndex& parent) const override;
            int columnCount(const QModelIndex& parent) const override;

            EngineCore::Scene* getScene();
        private:
            //QModelIndex getNodeIndex(EngineCore::Node* node);

        private:
            TreeItem* itemFromIndex(const QModelIndex& index) const;
            //TreeItem getItem(EngineCore::Node* node);

        private:
            TreeItem* _rootItem;
            EngineCore::Scene* m_scene;
        };
	}
}