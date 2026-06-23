#pragma once
#include <string>
#include <vector>

#include <rttr/registration>

namespace EngineCore
{
	class Scene;
	class IComponent;
	struct ComponentIterator
	{
	public:

		IComponent* component;
		void moveNext();
		bool operator ==(const ComponentIterator& arg);
	};


	class __declspec(dllexport) Node
	{
	public:
		virtual size_t getAddress();
		std::string& get_name();
		void set_name(std::string& name);
		void setName(const std::string& name) { m_name = name; }
	public:

		Node();
		virtual ~Node();
	public:
		Node* getParent() const;
		void setParent(Node* parent) { m_parent = parent; }

		// Component management
		void addComponent(IComponent* comp);
		void removeComponent(IComponent* comp);
		size_t getComponentCount() const { return m_components.size(); }
		IComponent* getComponent(size_t index) const;
		IComponent* getComponentByType(const std::string& type) const;
		std::vector<IComponent*>& getComponents() { return m_components; }

	protected:
		Node* m_parent;
		Scene* m_scene;
		std::string m_name;
		std::vector<IComponent*> m_components;

	};

	inline Node* Node::getParent() const
	{
		return m_parent;
	}

}