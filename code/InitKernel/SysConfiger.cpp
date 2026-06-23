#include "SysConfiger.h"
#include "IniParser.h"
#include "DeepWorldCore/DeepWorldApi/LogManagerInterface.h"
#include "DeepWorldCore/DeepWorldApi/MathTool.h"
#include <algorithm>
#include "DeepWorldCore/DeepWorldApi/StringTool.h"

static const char* sectionSeparator = "********************";

void SysConfiger::init(const std::string& sysConfigPath)
{
	IniParser iniParser;
	iniParser.load(sysConfigPath);
	parseCommonInfo(iniParser);
	parseHotKeyInfo(iniParser);
	parseLoggingLevel(iniParser);
	parseDebugInfo(iniParser);
	parseChromiumInfo(iniParser);
	parseEngineSettingConfig(iniParser);
	parseAttributeLabelConfig(iniParser);
	parseFormCustomization(iniParser);
	parseWebConfigItem(iniParser);
	parseApacheServerInfo(iniParser);
	parseNetworkRequestInfo(iniParser);
	parseSyncIntervalInfo(iniParser);
	//最后打印所有配置信息，所有解析配置信息的代码写在前面。
	//printSysConfig();
}

const CommonInfo& SysConfiger::getCommonInfo() const
{
	return m_commonInfo;
}


const std::vector<HotKeyItemInfo>& SysConfiger::getHotKeyInfo() const
{
	return m_hotKeyList;
}

const DebugInfo& SysConfiger::getDebugInfo() const
{
	return m_debugInfo;
}

const ChromiumInfo& SysConfiger::getChromiumInfo() const
{
	return m_chromiumInfo;
}

const Resafety::DeepWorld::EngineSettingConfig& SysConfiger::getEngineSettingConfig() const
{
	return m_engineSettingConfig;
}

int SysConfiger::getLoggingLevel() const
{
	return m_loggingLevel;
}


bool SysConfiger::getResistReplayAttacks()
{
	return m_bResistReplayAttacks;
}

bool SysConfiger::getUseRefreshToken()
{
	return m_bUseRefreshToken;
}

bool SysConfiger::getLoadNetResource()
{
	return m_bLoadNetResource;
}

bool SysConfiger::getUseRcloneState()
{
	return m_useRclone;
}

int SysConfiger::getSyncInterval()
{
	return m_syncInterval;
}

int SysConfiger::getEncryptionMode()
{
	return m_encryptionMode;
}

void SysConfiger::parseCommonInfo(const IniParser& iniParser)
{
	iniParser.getIntValue("Common", "MaxFrame", m_commonInfo.m_maxFrame, -1);
	iniParser.getIntValue("Common", "CoordinateMode", m_commonInfo.m_iCoordinateMode, 0);

	iniParser.getDoubleValue("Common", "rangeEast", m_commonInfo.rangeEast, -1.0);
	iniParser.getDoubleValue("Common", "rangeWest", m_commonInfo.rangeWest, -1.0);
	iniParser.getDoubleValue("Common", "rangeNorth", m_commonInfo.rangeNorth,-1.0);
	iniParser.getDoubleValue("Common", "rangeSouth", m_commonInfo.rangeSouth, -1.0);
	iniParser.getDoubleValue("Common", "mapscale", m_commonInfo.mapscale, -1.0);

	iniParser.getBoolValue("Common", "StopRenderingEnabled", m_commonInfo.m_stopRenderingEnabled, false);
	iniParser.getIntValue("Common", "StopRenderingTime", m_commonInfo.m_stopRenderingTime, 3600);
}


void SysConfiger::parseHotKeyInfo(const IniParser& iniParser)
{
	IniSection* hotKeySection = iniParser.getSection("HotKey");
	if (!hotKeySection)
		return;
	m_hotKeyList.reserve(hotKeySection->m_items.size());
	for (auto it = hotKeySection->begin(); it != hotKeySection->end(); it++)
	{
		m_hotKeyList.emplace_back(it->m_key, it->m_value);
	}
}

void SysConfiger::parseLoggingLevel(const IniParser& iniParser)
{
	iniParser.getIntValue("Log", "Level", m_loggingLevel, 2);
	if (m_loggingLevel < 0)
	{
		if (m_loggingLevel != -2)
			m_loggingLevel = 0;
	}
	if (m_loggingLevel > 4)
	{
		m_loggingLevel = 4;
	}
}

void SysConfiger::printSysConfig()
{
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%s%sSysConfig%s%s", sectionSeparator, sectionSeparator, sectionSeparator, sectionSeparator);
	printCommonInfo();
	printHotKeyInfo();
	printLoggingLevel();
	printEngineSettingConfig();
	printFormCustomization();
	printAttributeLabelConfig();
	printWebConfigItem();
	printApacheServerInfo();
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%s%s*********%s%s", sectionSeparator, sectionSeparator, sectionSeparator, sectionSeparator);
}

void SysConfiger::printCommonInfo()
{
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%sCommon%s", sectionSeparator, sectionSeparator);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"最大帧数:%d", m_commonInfo.m_maxFrame);
	//中间补充6个*，和开始处的长度对应
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%s******%s", sectionSeparator, sectionSeparator);
}

void SysConfiger::printHotKeyInfo()
{
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%sHotKey%s", sectionSeparator, sectionSeparator);
	for (const auto& hotKeyItem : m_hotKeyList)
	{
		Resafety::DeepWorld::GetLogManager()->logStandard(u8"name:%s,keyboardInfo:%s", hotKeyItem.name.c_str(), hotKeyItem.keyboardInfo.c_str());
	}
	//中间补充6个*，和开始处的长度对应
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%s******%s", sectionSeparator, sectionSeparator);
}

void SysConfiger::printLoggingLevel()
{
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%sLog%s", sectionSeparator, sectionSeparator);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"日志等级:%d", m_loggingLevel);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%s***%s", sectionSeparator, sectionSeparator);
}

void SysConfiger::printEngineSettingConfig()
{
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%sEngineSetting%s", sectionSeparator, sectionSeparator);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"DataLoadingThreadCount:%d", m_engineSettingConfig.dataLoadingThreadCount);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"GraphicsLoadingThreadCount:%d", m_engineSettingConfig.graphicsLoadingThreadCount);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"GraphicsRenderThreadCount:%d", m_engineSettingConfig.graphicsRenderThreadCount);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"MiscAssetLoadingThreadCount:%d", m_engineSettingConfig.miscAssetLoadingThreadCount);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"PickLoadingThreadCount:%d", m_engineSettingConfig.pickLoadingThreadCount);
	Resafety::DeepWorld::GetLogManager()->logStandard(u8"%s*********%s", sectionSeparator, sectionSeparator);
}

void SysConfiger::parseDebugInfo(const IniParser& iniParser)
{
	iniParser.getBoolValue("Debug", "Open", m_debugInfo.m_openDebug, false);
	//iniParser.getBoolValue("Debug", "LayerRefresh", m_debugInfo.m_layerRefresh, true);
	wchar_t szBuf[1024];
	memset(szBuf, 0, 1024);
	std::wstring wIniFilePath = StringTool::utfString2WString(iniParser.m_filePath);
	DWORD dwCount = GetPrivateProfileStringW(L"Debug", L"LayerRefresh", NULL, szBuf, 1024, wIniFilePath.c_str());
	if (dwCount > 0)
	{
		m_debugInfo.m_layerRefresh = _wtoi(szBuf) == 0 ? false : true;
	}
}

void SysConfiger::parseChromiumInfo(const IniParser& iniParser)
{
	double lessen = 0;
	iniParser.getDoubleValue("Chromium", "Lessen", lessen, 1.0);

	if (lessen > 0)
	{
		m_chromiumInfo.m_lessen = lessen;
		MathTool::SteLessen(lessen);
	}
}

void SysConfiger::parseEngineSettingConfig(const IniParser& iniParser)
{
	int dataLoadingThreadCount = 0;
	int graphicsLoadingThreadCount = 0;
	int graphicsRenderThreadCount = 0;
	int pickLoadingThreadCount = 0;
	int miscAssetLoadingThreadCount = 0;
	iniParser.getIntValue("EngineSetting", "DataLoadingThreadCount", dataLoadingThreadCount, 8);
	iniParser.getIntValue("EngineSetting", "GraphicsLoadingThreadCount", graphicsLoadingThreadCount, 4);
	iniParser.getIntValue("EngineSetting", "GraphicsRenderThreadCount", graphicsRenderThreadCount, 1);
	iniParser.getIntValue("EngineSetting", "PickLoadingThreadCount", pickLoadingThreadCount, 1);
	iniParser.getIntValue("EngineSetting", "MiscAssetLoadingThreadCount", miscAssetLoadingThreadCount, 4);
	m_engineSettingConfig.dataLoadingThreadCount = (uint32_t)dataLoadingThreadCount;
	m_engineSettingConfig.graphicsLoadingThreadCount = (uint32_t)graphicsLoadingThreadCount;
	m_engineSettingConfig.graphicsRenderThreadCount = (uint32_t)graphicsRenderThreadCount;
	m_engineSettingConfig.pickLoadingThreadCount = (uint32_t)pickLoadingThreadCount;
	m_engineSettingConfig.miscAssetLoadingThreadCount = (uint32_t)miscAssetLoadingThreadCount;

	bool dataAsyncDeleting = false;
	bool graphicsAssetAsyncDeleting = false;
	bool miscAssetAsyncDeleting = false;
	bool pickAssetAsyncDeleting = false;
	iniParser.getBoolValue("EngineSetting", "DataAsyncDeleting", dataAsyncDeleting, false);
	iniParser.getBoolValue("EngineSetting", "GraphicsAssetAsyncDeleting", graphicsAssetAsyncDeleting, false);
	iniParser.getBoolValue("EngineSetting", "MiscAssetAsyncDeleting", miscAssetAsyncDeleting, false);
	iniParser.getBoolValue("EngineSetting", "PickAssetAsyncDeleting", pickAssetAsyncDeleting, false);
	m_engineSettingConfig.dataAsyncDeleting = dataAsyncDeleting;
	m_engineSettingConfig.graphicsAssetAsyncDeleting = graphicsAssetAsyncDeleting;
	m_engineSettingConfig.miscAssetAsyncDeleting = miscAssetAsyncDeleting;
	m_engineSettingConfig.pickAssetAsyncDeleting = pickAssetAsyncDeleting;
}

void SysConfiger::parseFormCustomization(const IniParser& iniParser)
{
	std::string tables = "";
	iniParser.getStringValue("FormCustomization", "Table", tables, "");
	if (tables.empty())
	{
		return;
	}
	
	std::vector<std::string> subStringList = StringTool::Split(tables, ",");
	if (subStringList.size() < 1)
	{
		return;
	}

	for (auto& table : subStringList)
	{
		IniSection* tableSection = iniParser.getSection(table);
		if (!tableSection)
			continue;

		std::vector<Resafety::DeepWorld::FormCustomizationFieldInfo> fieldList;
		for (auto it = tableSection->begin(); it != tableSection->end(); ++it)
		{
			Resafety::DeepWorld::FormCustomizationFieldInfo fieldInfo(it->m_key, it->m_value);
			fieldList.push_back(fieldInfo);
		}
		if (fieldList.size() >= 1)
		{
			m_tableAttributeFieldList.insert(std::pair<std::string, std::vector<Resafety::DeepWorld::FormCustomizationFieldInfo>>(table, fieldList));
		}
	}
}

void SysConfiger::parseAttributeLabelConfig(const IniParser& iniParser)
{
	bool dragEnabled = false;
	bool handle = false;
	double colorA, colorR, colorG, colorB;
	int handleWidth;
	double nameMaxLength, valueMaxLength;
	iniParser.getBoolValue("AttributeLabel", "DragEnabled", m_attributeLabelInfo.dragEnabled, false);
	iniParser.getBoolValue("AttributeLabel", "Handle", m_attributeLabelInfo.handle, false);
	iniParser.getDoubleValue("AttributeLabel", "HandleColor_a", colorA, 1);
	iniParser.getDoubleValue("AttributeLabel", "HandleColor_r", colorR, 1);
	iniParser.getDoubleValue("AttributeLabel", "HandleColor_g", colorG, 1);
	iniParser.getDoubleValue("AttributeLabel", "HandleColor_b", colorB, 1);
	iniParser.getIntValue("AttributeLabel", "HandleWidth", handleWidth, 30);
	iniParser.getDoubleValue("AttributeLabel", "NameMaxLength", nameMaxLength, 100);
	iniParser.getDoubleValue("AttributeLabel", "ValueMaxLength", valueMaxLength, 500);
	iniParser.getIntValue("AttributeLabel", "NameHAlignment", m_attributeLabelInfo.nameHAlignment, 2);
	iniParser.getIntValue("AttributeLabel", "ValueHAlignment", m_attributeLabelInfo.valueHAlignment, 2);
	iniParser.getIntValue("AttributeLabel", "NameVAlignment", m_attributeLabelInfo.nameVAlignment, 2);
	iniParser.getIntValue("AttributeLabel", "ValueVAlignment", m_attributeLabelInfo.valueVAlignment, 2);
	m_attributeLabelInfo.handleColor.a = static_cast<float>(colorA);
	m_attributeLabelInfo.handleColor.r = static_cast<float>(colorR);
	m_attributeLabelInfo.handleColor.g = static_cast<float>(colorG);
	m_attributeLabelInfo.handleColor.b = static_cast<float>(colorB);
	m_attributeLabelInfo.handleWidth = static_cast<int>(handleWidth);
	m_attributeLabelInfo.nameMaxLength = static_cast<float>(nameMaxLength);
	m_attributeLabelInfo.valueMaxLength = static_cast<float>(valueMaxLength);
}

void SysConfiger::parseWebConfigItem(const IniParser& iniParser)
{
	// 云渲染相关配置，这些字段由render_server读写；
	// 使用平行云larkXR时，这些字段可省略；
	//为兼容平台2.0的配置项，ini中配置项采用下划线的命名方式；
	iniParser.getIntValue("WebConfigItem", "fixed_config", m_webConfigItem.m_fixedConfig, 0);
	iniParser.getStringValue("WebConfigItem", "exe_name", m_webConfigItem.m_exeName, "");
	iniParser.getStringValue("WebConfigItem", "exe_path", m_webConfigItem.m_exePath, "");
}

void SysConfiger::parseApacheServerInfo(const IniParser& iniParser)
{
	iniParser.getIntValue("ApacheServerInfo", "port", m_apacheServerInfo.m_port, 0);
	iniParser.getStringValue("ApacheServerInfo", "hostIp", m_apacheServerInfo.m_hostIp, "");
}

void SysConfiger::parseNetworkRequestInfo(const IniParser& iniParser)
{
	iniParser.getIntValue("NetworkRequest", "ResistReplayAttacks", m_bResistReplayAttacks, 0);
	iniParser.getIntValue("NetworkRequest", "UseRefTok", m_bUseRefreshToken, 1);
	iniParser.getIntValue("NetworkRequest", "loadNetResource", m_bLoadNetResource, 1);
	iniParser.getIntValue("NetworkRequest", "UseRclone", m_useRclone, 0);
	iniParser.getIntValue("NetworkRequest", "EncryptionMode", m_encryptionMode, 0);	
}

void SysConfiger::parseSyncIntervalInfo(const IniParser& iniParser)
{
	iniParser.getIntValue("EngineSetting", "SyncInterval", m_syncInterval, 0);
}