#include "Node.h"
#include "Component.h"
#include <string>

namespace EngineCore
{

	bool ComponentIterator::operator == (const ComponentIterator& arg)
	{
		return component == arg.component;
	}

	Node::Node() :
		m_parent(nullptr),
		m_scene(nullptr)
	{
	}

	Node::~Node()
	{
		for (auto comp : m_components)
		{
			delete comp;
		}
		m_components.clear();
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Node>("EngineCore::Node")
			.constructor<>()
			.property("name", &Node::get_name, &Node::set_name)
		;
	}

	size_t Node::getAddress()
	{
		return (size_t)this;
	}

	void Node::set_name(std::string& name)
	{
		if (m_name.compare(name) != 0)
		{
			m_name = name;
		}
	}

	std::string& Node::get_name()
	{
		return m_name;
	}

	void Node::addComponent(IComponent* comp)
	{
		if (comp)
		{
			m_components.push_back(comp);
		}
	}

	void Node::removeComponent(IComponent* comp)
	{
		auto it = std::find(m_components.begin(), m_components.end(), comp);
		if (it != m_components.end())
		{
			m_components.erase(it);
		}
	}

	IComponent* Node::getComponent(size_t index) const
	{
		if (index < m_components.size())
			return m_components[index];
		return nullptr;
	}

	IComponent* Node::getComponentByType(const std::string& type) const
	{
		for (auto comp : m_components)
		{
			if (comp->getComponetType() == type)
				return comp;
		}
		return nullptr;
	}

}