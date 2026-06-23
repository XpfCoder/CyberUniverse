#include "SceneTreeModel.h"
#include "TreeItem.h"
namespace Resafety {
	namespace CyberUniverseStudio {




        SceneTreeModel::SceneTreeModel(QObject* parent)
            : QAbstractItemModel(parent)
        {
            _rootItem = new TreeItem();
            
        }

        SceneTreeModel::~SceneTreeModel()
        {
            delete _rootItem;
        }

        TreeItem* SceneTreeModel::itemFromIndex(const QModelIndex& index) const
        {
            if (index.isValid())
            {
                TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
                return item;
            }
            return _rootItem;
        }

        TreeItem* SceneTreeModel::root()
        {
            return _rootItem;
        }

        // 获取表头数据
        QVariant SceneTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
        {
            return QVariant();
        }

        // 获取index.row行，index.column列数据
        QVariant SceneTreeModel::data(const QModelIndex& index, int role) const
        {
            if (!index.isValid())
                return QVariant();
            EngineCore::Node* node = (EngineCore::Node*)index.internalPointer();
            TreeItem* item = itemFromIndex(index);
            if (role == Qt::DisplayRole)
            {
                return item->data(index.column());
            }
            return QVariant();
        }

        // 在parent节点下，第row行，第column列位置上创建索引
        QModelIndex SceneTreeModel::index(int row, int column, const QModelIndex& parent) const
        {
            if (!hasIndex(row, column, parent))
                return QModelIndex();

            TreeItem* parentItem = itemFromIndex(parent);
            TreeItem* item = parentItem->child(row);
            if (item)
                return createIndex(row, column, item);
            else
                return QModelIndex();
        }

        // 创建index的父索引
        QModelIndex SceneTreeModel::parent(const QModelIndex& index) const
        {
            if (!index.isValid())
                return QModelIndex();

            TreeItem* item = itemFromIndex(index);
            TreeItem* parentItem = item->parent();

            if (parentItem == _rootItem)
                return QModelIndex();
            return createIndex(parentItem->row(), 0, parentItem);
        }

        // 获取索引parent下有多少行
        int SceneTreeModel::rowCount(const QModelIndex& parent) const
        {
            if (parent.column() > 0)
                return 0;

            TreeItem* item = itemFromIndex(parent);
            return item->childCount();
        }

        // 返回索引parent下有多少列
        int SceneTreeModel::columnCount(const QModelIndex& parent) const
        {
            return 1;
            //return _headers.size();
        }

        EngineCore::Scene* SceneTreeModel::getScene()
        {
            return m_scene;
        }

        //QModelIndex SceneTreeModel::getNodeIndex(EngineCore::Node* node)
        //{
        //    if (TreeItem item = getItem(node))
        //    {
        //        return this->createIndex(item->index, 0, node);
        //    }

        //    return QModelIndex();
        //}

        //TreeItem SceneTreeModel::getItem(EngineCore::Node* node)
        //{
        //    //auto iter = m_nodeItem.find(node);
        //    //if (iter != m_nodeItem.end())
        //    //{
        //    //    return iter->second;
        //    //}
        //    return TreeItem();
        //}

	}
}