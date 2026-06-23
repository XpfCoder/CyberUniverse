#include "TreeItem.h"
#include "../CyberUniverseGeo/Scene/GeoNode.h"
#include "../EngineCore/Core/Engine/Component.h"
#include "../EngineCore/Core/Engine/Node.h"
namespace Resafety {
	namespace CyberUniverseStudio {


        TreeItem::TreeItem(TreeItem* parent)
            : _parent(parent),
            _ptr(nullptr),
            _row(-1)
        {

        }

        TreeItem::~TreeItem()
        {
            removeChildren();
        }

        void TreeItem::addChild(TreeItem* item)
        {
            item->setRow(_children.size());
            _children.append(item);
        }

        void TreeItem::removeChildren()
        {
            qDeleteAll(_children);
            _children.clear();
        }

        QVariant TreeItem::data(int column) const
        {
            if (_ptr == nullptr)
                return QVariant();

            EngineCore::Node* p = static_cast<EngineCore::Node*>(_ptr);
            if (p)
                return QString(p->get_name().c_str());

            return QVariant();
        }





	}
}
