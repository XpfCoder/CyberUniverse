#include "CorePlugin.h"
#include "LoginWidget.h"
//#include "CoreObject.h"
#include "PluginManager.h"
#include "../../thirdparty/rapidjson/include/rapidjson/rapidjson.h"
#include "../../thirdparty/rapidjson/include/rapidjson/document.h"

using namespace Resafety::CyberUniverseStudio;

bool CorePlugin::load(ICore* core)
{
	//auto coreObject = CoreObject::instance();
	//coreObject->init();

	LoginWidget * login = new LoginWidget();

	auto pluginManager = PluginManager::instance();
	pluginManager->search();
	login->show();

	QString name = "CorePlugin";
	pluginManager->addPlugin(name, this);  //向m_objects添加插件信息

	return true;
}

//void handlePrint(CoreObject* coreObject, const rapidjson::Value& arrParam)
//{
//	coreObject->onPrint();
//}
//void handlePrintPreview(CoreObject* coreObject, const rapidjson::Value& arrParam)
//{
//	coreObject->onPrintPreview();
//}
//void handlePrintSet(CoreObject* coreObject, const rapidjson::Value& arrParam)
//{
//	coreObject->onPrintSet();
//}
bool CorePlugin::pluginHandle(const std::string& jsonStrs)
{
	rapidjson::Document document;
	document.Parse(jsonStrs.c_str());
	std::string funcName = "";
	rapidjson::Value::ConstMemberIterator itrm = document.FindMember("func");
	if (itrm != document.MemberEnd())
		funcName = itrm->value.GetString();
	//if (funcName.empty())
	//{
	//	LogInfoEx(__FUNCTION__, u8"调用函数名为空");
	//	return true;
	//}
	//itrm = document.FindMember("params");
	/*auto coreObject = CoreObject::instance();
	if (itrm != document.MemberEnd() && rapidjson::kArrayType == itrm->value.GetType())
	{
		const rapidjson::Value& arrParam = itrm->value;
		if ("print" == funcName)
		{
			handlePrint(coreObject, arrParam);
		}
		else if ("printPreview" == funcName)
		{
			handlePrintPreview(coreObject, arrParam);
		}
		else if ("printSet" == funcName)
		{
			handlePrintSet(coreObject, arrParam);
		}
	}*/
	return true;
}