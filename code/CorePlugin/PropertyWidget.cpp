#include <QMainWindow>
#include <QDir>
#include <QApplication>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include "PropertyWidget.h"
#include "CoreObject.h"
#include "../EngineCore/Core/Engine/Node.h"
#include "../EngineCore/Core/Engine/Component.h"
#include "../EngineCore/Scene/Component/Common/Transform.h"
#include "../EngineCore/Scene/Component/Common/Material.h"

// rttr registration for math types
RTTR_REGISTRATION
{
	rttr::registration::class_<DirectX::XMFLOAT3>("DirectX::XMFLOAT3")
		.constructor<>()
		.property("x", &DirectX::XMFLOAT3::x)
		.property("y", &DirectX::XMFLOAT3::y)
		.property("z", &DirectX::XMFLOAT3::z)
	;
	rttr::registration::class_<DirectX::XMFLOAT4>("DirectX::XMFLOAT4")
		.constructor<>()
		.property("x", &DirectX::XMFLOAT4::x)
		.property("y", &DirectX::XMFLOAT4::y)
		.property("z", &DirectX::XMFLOAT4::z)
		.property("w", &DirectX::XMFLOAT4::w)
	;
	rttr::registration::class_<EngineCore::Transform>("EngineCore::Transform")
		.constructor<>()
		.property("Position", &EngineCore::Transform::getPosition, &EngineCore::Transform::setPosition)
		.property("Rotation", &EngineCore::Transform::getRotation, &EngineCore::Transform::setRotation)
		.property("Scale", &EngineCore::Transform::getScale, &EngineCore::Transform::setScale)
	;
	rttr::registration::class_<EngineCore::Material>("EngineCore::Material")
		.constructor<>()
		.property("Ambient", &EngineCore::Material::ambient)
		.property("Diffuse", &EngineCore::Material::diffuse)
		.property("Specular", &EngineCore::Material::specular)
		.property("Reflect", &EngineCore::Material::reflect)
	;
}

static QVariant xmf3ToQVariant(const DirectX::XMFLOAT3& v)
{
	return QVariant(QString("%1, %2, %3").arg(v.x, 0, 'f', 3).arg(v.y, 0, 'f', 3).arg(v.z, 0, 'f', 3));
}

static QVariant xmf4ToQVariant(const DirectX::XMFLOAT4& v)
{
	return QVariant(QString("%1, %2, %3, %4").arg(v.x, 0, 'f', 3).arg(v.y, 0, 'f', 3).arg(v.z, 0, 'f', 3).arg(v.w, 0, 'f', 3));
}

static void populateFloat3SubItems(QTreeWidgetItem* parent, const std::string& label,
	const DirectX::XMFLOAT3& val,
	EngineCore::IComponent* comp,
	void(*setter)(EngineCore::IComponent*, const DirectX::XMFLOAT3&))
{
	parent->setText(0, label.c_str());
	parent->setText(1, xmf3ToQVariant(val).toString());
	parent->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(comp)));
	parent->setData(0, Qt::UserRole + 1, QVariant::fromValue(reinterpret_cast<quintptr>(setter)));

	QTreeWidgetItem* xItem = new QTreeWidgetItem(parent);
	xItem->setText(0, "x");
	xItem->setFlags(xItem->flags() | Qt::ItemIsEditable);
	xItem->setText(1, QString::number(val.x, 'f', 3));
	xItem->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(comp)));
	xItem->setData(0, Qt::UserRole + 1, QVariant::fromValue(reinterpret_cast<quintptr>(setter)));
	xItem->setData(0, Qt::UserRole + 2, 0);

	QTreeWidgetItem* yItem = new QTreeWidgetItem(parent);
	yItem->setText(0, "y");
	yItem->setFlags(yItem->flags() | Qt::ItemIsEditable);
	yItem->setText(1, QString::number(val.y, 'f', 3));
	yItem->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(comp)));
	yItem->setData(0, Qt::UserRole + 1, QVariant::fromValue(reinterpret_cast<quintptr>(setter)));
	yItem->setData(0, Qt::UserRole + 2, 1);

	QTreeWidgetItem* zItem = new QTreeWidgetItem(parent);
	zItem->setText(0, "z");
	zItem->setFlags(zItem->flags() | Qt::ItemIsEditable);
	zItem->setText(1, QString::number(val.z, 'f', 3));
	zItem->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(comp)));
	zItem->setData(0, Qt::UserRole + 1, QVariant::fromValue(reinterpret_cast<quintptr>(setter)));
	zItem->setData(0, Qt::UserRole + 2, 2);
}

static void populateFloat4SubItems(QTreeWidgetItem* parent, const std::string& label,
	const DirectX::XMFLOAT4& val,
	void(*setter)(EngineCore::Material&, int, float))
{
	parent->setText(0, label.c_str());
	parent->setText(1, xmf4ToQVariant(val).toString());
	parent->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(setter)));

	QTreeWidgetItem* xItem = new QTreeWidgetItem(parent);
	xItem->setText(0, "r");
	xItem->setFlags(xItem->flags() | Qt::ItemIsEditable);
	xItem->setText(1, QString::number(val.x, 'f', 3));
	xItem->setData(0, Qt::UserRole, 0);

	QTreeWidgetItem* yItem = new QTreeWidgetItem(parent);
	yItem->setText(0, "g");
	yItem->setFlags(yItem->flags() | Qt::ItemIsEditable);
	yItem->setText(1, QString::number(val.y, 'f', 3));
	yItem->setData(0, Qt::UserRole, 1);

	QTreeWidgetItem* zItem = new QTreeWidgetItem(parent);
	zItem->setText(0, "b");
	zItem->setFlags(zItem->flags() | Qt::ItemIsEditable);
	zItem->setText(1, QString::number(val.z, 'f', 3));
	zItem->setData(0, Qt::UserRole, 2);

	QTreeWidgetItem* wItem = new QTreeWidgetItem(parent);
	wItem->setText(0, "a");
	wItem->setFlags(wItem->flags() | Qt::ItemIsEditable);
	wItem->setText(1, QString::number(val.w, 'f', 3));
	wItem->setData(0, Qt::UserRole, 3);
}

static void setTransformPosition(EngineCore::IComponent* comp, const DirectX::XMFLOAT3& val) { comp->setPosition(val); comp->applyChanges(); }
static void setTransformRotation(EngineCore::IComponent* comp, const DirectX::XMFLOAT3& val) { comp->setRotation(val); comp->applyChanges(); }
static void setTransformScale(EngineCore::IComponent* comp, const DirectX::XMFLOAT3& val) { comp->setScale(val); comp->applyChanges(); }

CyberUniversePropertyTreeWidget::CyberUniversePropertyTreeWidget(QWidget* parent) :
	QTreeWidget(parent)
{
	setColumnCount(2);
	setHeaderLabels(QStringList() << "Property" << "Value");
	header()->setStretchLastSection(true);
	setColumnWidth(0, 170);
	setAnimated(true);

	connect(this, &QTreeWidget::itemChanged, [this](QTreeWidgetItem* item, int column) {
		if (column != 1 || !item) return;

		QString newValue = item->text(1);
		QTreeWidgetItem* parentItem = item->parent();
		if (!parentItem) return;

		// --- Case 1: Transform sub-item (x/y/z child of Position/Rotation/Scale) ---
		quintptr compPtr = parentItem->data(0, Qt::UserRole).value<quintptr>();
		quintptr setterFunc = parentItem->data(0, Qt::UserRole + 1).value<quintptr>();
		int subIdx = parentItem->indexOfChild(item);

		if (compPtr && setterFunc && subIdx >= 0)
		{
			EngineCore::IComponent* comp = reinterpret_cast<EngineCore::IComponent*>(compPtr);
			auto setter = reinterpret_cast<void(*)(EngineCore::IComponent*, const DirectX::XMFLOAT3&)>(setterFunc);
			if (comp && setter)
			{
				DirectX::XMFLOAT3 val = comp->getPosition();
				if (setter == setTransformRotation) val = comp->getRotation();
				else if (setter == setTransformScale) val = comp->getScale();

				float newF = newValue.toFloat();
				switch (subIdx)
				{
				case 0: val.x = newF; break;
				case 1: val.y = newF; break;
				case 2: val.z = newF; break;
				}
				setter(comp, val);
				parentItem->setText(1, xmf3ToQVariant(val).toString());
				emit propertyChanged();
			}
			return;
		}

		// --- Case 2: Material float4 sub-items (r/g/b/a child of Ambient/Diffuse/etc) ---
		QTreeWidgetItem* matGroupItem = parentItem;
		QTreeWidgetItem* compGroupItem = matGroupItem->parent();
		if (compGroupItem)
		{
			quintptr matCompPtr = compGroupItem->data(0, Qt::UserRole).value<quintptr>();
			if (matCompPtr)
			{
				EngineCore::IComponent* comp = reinterpret_cast<EngineCore::IComponent*>(matCompPtr);
				if (comp)
				{
					int colorIdx = item->data(0, Qt::UserRole).toInt();
					if (colorIdx >= 0 && colorIdx <= 3)
					{
						EngineCore::Material mat = comp->getMaterial();
						float val = newValue.toFloat();
						DirectX::XMFLOAT4* target = nullptr;
						std::string matName = matGroupItem->text(0).toStdString();
						if (matName == "Ambient") target = &mat.ambient;
						else if (matName == "Diffuse") target = &mat.diffuse;
						else if (matName == "Specular") target = &mat.specular;
						else if (matName == "Reflect") target = &mat.reflect;

						if (target)
						{
							switch (colorIdx) {
							case 0: target->x = val; break;
							case 1: target->y = val; break;
							case 2: target->z = val; break;
							case 3: target->w = val; break;
							}
							comp->setMaterial(mat);
							emit propertyChanged();
						}
					}
				}
				return;
			}
		}

		// --- Case 3: Name change ---
		if (item->text(0) == "name")
		{
			quintptr nodePtr = item->data(0, Qt::UserRole).value<quintptr>();
			if (nodePtr)
			{
				std::string newName = newValue.toStdString();
				reinterpret_cast<EngineCore::Node*>(nodePtr)->setName(newName);
			}
			return;
		}
	});
}

CyberUniversePropertyTreeWidget::~CyberUniversePropertyTreeWidget()
{
}

QMainWindow* CyberUniversePropertyTreeWidget::getMainWindow()
{
	return m_mainWnd;
}

void CyberUniversePropertyTreeWidget::setLock(bool val)
{
	m_lock = val;
}

void CyberUniversePropertyTreeWidget::setNode(EngineCore::Node* node)
{
	if (m_lock) return;
	if (m_node == node) return;

	m_node = node;
	refreshProperty();
}

void CyberUniversePropertyTreeWidget::refreshProperty()
{
	this->clear();
	if (!m_node)
	{
		setWindowTitle("Node: ");
		return;
	}

	setWindowTitle(QString("Node: %1").arg(m_node->get_name().c_str()));
	buildPropertyTree();
}

void CyberUniversePropertyTreeWidget::buildPropertyTree()
{
	if (!m_node) return;

	// Node properties group
	{
		QTreeWidgetItem* groupItem = new QTreeWidgetItem(this);
		groupItem->setText(0, "Node");
		groupItem->setFlags(groupItem->flags() | Qt::ItemIsEnabled);
		groupItem->setExpanded(true);

		QTreeWidgetItem* nameItem = new QTreeWidgetItem(groupItem);
		nameItem->setText(0, "name");
		nameItem->setFlags(nameItem->flags() | Qt::ItemIsEditable);
		nameItem->setText(1, m_node->get_name().c_str());
		// Store a pointer to the node for name changes
		nameItem->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(m_node)));
	}

	// Per-component property groups
	for (size_t i = 0; i < m_node->getComponentCount(); ++i)
	{
		EngineCore::IComponent* comp = m_node->getComponent(i);
		if (!comp) continue;

		std::string groupName = comp->getComponetType().empty() ? "Component" : comp->getComponetType();
		QTreeWidgetItem* compGroup = new QTreeWidgetItem(this);
		compGroup->setText(0, groupName.c_str());
		compGroup->setFlags(compGroup->flags() | Qt::ItemIsEnabled);
		compGroup->setExpanded(true);
		compGroup->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(comp)));

		// UUID (read-only)
		QTreeWidgetItem* uuidItem = new QTreeWidgetItem(compGroup);
		uuidItem->setText(0, "uuid");
		uuidItem->setText(1, comp->getUuId().c_str());

		// Texture
		QTreeWidgetItem* texItem = new QTreeWidgetItem(compGroup);
		texItem->setText(0, "texture");
		texItem->setFlags(texItem->flags() | Qt::ItemIsEditable);
		texItem->setText(1, comp->getTexture().c_str());

		// Transform group
		QTreeWidgetItem* xformGroup = new QTreeWidgetItem(compGroup);
		xformGroup->setText(0, "Transform");
		xformGroup->setFlags(xformGroup->flags() | Qt::ItemIsEnabled);
		xformGroup->setExpanded(true);

		DirectX::XMFLOAT3 pos = comp->getPosition();
		DirectX::XMFLOAT3 rot = comp->getRotation();
		DirectX::XMFLOAT3 scale = comp->getScale();

		QTreeWidgetItem* posItem = new QTreeWidgetItem(xformGroup);
		populateFloat3SubItems(posItem, "Position", pos, comp, setTransformPosition);

		QTreeWidgetItem* rotItem = new QTreeWidgetItem(xformGroup);
		populateFloat3SubItems(rotItem, "Rotation", rot, comp, setTransformRotation);

		QTreeWidgetItem* scaleItem = new QTreeWidgetItem(xformGroup);
		populateFloat3SubItems(scaleItem, "Scale", scale, comp, setTransformScale);

		// Material group
		QTreeWidgetItem* matGroup = new QTreeWidgetItem(compGroup);
		matGroup->setText(0, "Material");
		matGroup->setFlags(matGroup->flags() | Qt::ItemIsEnabled);
		matGroup->setExpanded(false);
		matGroup->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(comp)));

		EngineCore::Material mat = comp->getMaterial();

		QTreeWidgetItem* ambientItem = new QTreeWidgetItem(matGroup);
		populateFloat4SubItems(ambientItem, "Ambient", mat.ambient, nullptr);

		QTreeWidgetItem* diffuseItem = new QTreeWidgetItem(matGroup);
		populateFloat4SubItems(diffuseItem, "Diffuse", mat.diffuse, nullptr);

		QTreeWidgetItem* specularItem = new QTreeWidgetItem(matGroup);
		populateFloat4SubItems(specularItem, "Specular", mat.specular, nullptr);

		QTreeWidgetItem* reflectItem = new QTreeWidgetItem(matGroup);
		populateFloat4SubItems(reflectItem, "Reflect", mat.reflect, nullptr);
	}

	expandAll();
}


PropertyEditWidget::PropertyEditWidget(QWidget* parent)
	: QDockWidget(parent)
{
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	setWindowTitle(QObject::tr("Properties"));

	m_propertyTree = new CyberUniversePropertyTreeWidget(this);
	m_propertyTree->SetMainWindow((QMainWindow*)parent);
	m_propertyTree->setObjectName("ComTreeView");

	layout->addWidget(m_propertyTree);
	setWidget(m_propertyTree);

	connect(m_propertyTree, &CyberUniversePropertyTreeWidget::propertyChanged, this, &PropertyEditWidget::propertyChanged);
}

PropertyEditWidget::~PropertyEditWidget()
{
}

void PropertyEditWidget::setNode(EngineCore::Node* node)
{
	if (m_node == node) return;
	m_node = node;
	m_propertyTree->setNode(node);
}
