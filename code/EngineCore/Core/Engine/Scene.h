#include "Node.h"

namespace EngineCore
{
	class __declspec(dllexport) Scene : public EngineCore::Node
	{
	public:
		virtual size_t getAddress();
		Node* getRootNode() const;
		Node* getFirstTopNode() const;
		Node* getLastTopNode() const;

		Scene* getNextScene() const;
	protected:
		Node* m_rootNode{ nullptr };

	};



}