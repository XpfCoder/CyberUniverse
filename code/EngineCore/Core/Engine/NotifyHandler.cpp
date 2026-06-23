#include "NotifyHandler.h"

namespace EngineCore
{
	size_t NotifyHandler::getAddress()
	{
		return (size_t)this;
	}

	size_t PropertyChangedNotifyHandler::getAddress()
	{
		return (size_t)this;
	}

	void PropertyChangedNotifyHandler::onPropertyChanged(Reference* sender, std::string& propertyName, PropertyChangedFlag flag, Iterator* iterator)
	{

	}

	void PropertyChangedNotifyHandler::onPropertyAvailabilityChanged(Reference* sender, std::string& propertyName)
	{

	}

	void PropertyChangedNotifyHandler::onDynamicPropertyChanged(Reference* sender, std::string& propertyName, PropertyChangedFlag flag, Iterator* iterator)
	{

	}

	void PropertyChangedNotifyHandler::onUpdateDynamicProperty(Reference* sender)
	{
	}

}
