#pragma once
#include <string>
#include <map>
#include "SysConfigerInterface.h"

class IniParser;
class SysConfiger : public ISysConfiger
{
public:
	virtual void init(const std::string& sysConfigPath) override;
	virtual const CommonInfo& getCommonInfo() const override;
	virtual const std::vector<HotKeyItemInfo>& getHotKeyInfo() const override;
	virtual int getLoggingLevel() const override;
	virtual const DebugInfo& getDebugInfo() const override;
	virtual const ChromiumInfo& getChromiumInfo()const override;
	virtual const Resafety::DeepWorld::EngineSettingConfig& getEngineSettingConfig() const override;
	virtual bool getResistReplayAttacks() override;
	virtual bool getUseRefreshToken() override;
	virtual bool getLoadNetResource() override;
	virtual bool getUseRcloneState() override;
	virtual int getSyncInterval() override;
	virtual int getEncryptionMode() override;
public:
	/*!
	* @brief 将所有的系统配置项打印到日志文件中，方便查看。
	* @remark 在新添加配置项时，必须打印对应的配置项
	*/
	virtual void printSysConfig() override;
private:
	void parseCommonInfo(const IniParser& iniParser);
	void parseHotKeyInfo(const IniParser& iniParser);
	void parseLoggingLevel(const IniParser& iniParser);
	void parseDebugInfo(const IniParser& iniParser);
	void parseChromiumInfo(const IniParser& iniParser);
	void parseEngineSettingConfig(const IniParser& iniParser);
	void parseFormCustomization(const IniParser& iniParser);
	void parseAttributeLabelConfig(const IniParser& iniParser);
	void parseWebConfigItem(const IniParser& iniParser);
	void parseApacheServerInfo(const IniParser& iniParser);
	void parseNetworkRequestInfo(const IniParser& iniParser);
	void parseSyncIntervalInfo(const IniParser& iniParser);
private:
	void printCommonInfo();
	void printHotKeyInfo();
	void printLoggingLevel();
	void printEngineSettingConfig();
	void printFormCustomization();
	void printAttributeLabelConfig();
	void printWebConfigItem();
	void printApacheServerInfo();
private:
	CommonInfo m_commonInfo;
	std::vector<HotKeyItemInfo> m_hotKeyList;
	int m_loggingLevel{ 2 };
	DebugInfo	m_debugInfo;
	ChromiumInfo	m_chromiumInfo;
	Resafety::DeepWorld::EngineSettingConfig m_engineSettingConfig;
	std::map<std::string, std::vector<Resafety::DeepWorld::FormCustomizationFieldInfo>> m_tableAttributeFieldList;
	Resafety::DeepWorld::AttributeLabelInfo m_attributeLabelInfo;
	WebConfigItem m_webConfigItem;
	ApacheServerInfo m_apacheServerInfo;
	int m_bResistReplayAttacks = 0;
	int m_bUseRefreshToken = 1;
	int m_bLoadNetResource = 1;
	int m_useRclone = 0;
	int m_syncInterval = 0;
	int m_encryptionMode = 0;
};