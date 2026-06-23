#pragma once
#include <vector>
#include <string>
#include <map>

#include "../DeepWorldCore/HotKey/HotKeyItemInfo.h"
#include "../DeepWorldCore/DeepWorldApi/FrameworkInterface.h"

struct CommonInfo
{
	int m_maxFrame{ 0 };
	int m_iCoordinateMode{ 0 };
	double rangeEast = -1.0;
	double rangeWest = -1.0;
	double rangeNorth = -1.0;
	double rangeSouth = -1.0;
	double mapscale = -1.0;
	bool m_stopRenderingEnabled{ false };
	int m_stopRenderingTime = 3600;
};

//Debug¿ª¹Ø
struct DebugInfo
{
	bool m_openDebug{ false };
	bool m_layerRefresh{ true };
};

struct ChromiumInfo
{
	double m_lessen{ 1.0 };
};

struct WebConfigItem
{
	int m_fixedConfig{ 1 };
	std::string m_exeName;
	std::string m_exePath;
};

struct ApacheServerInfo
{
	std::string m_hostIp;
	int m_port{ 30080 };
};

class ISysConfiger
{
public:
	virtual ~ISysConfiger() = default;
	virtual void init(const std::string& sysConfigPath) = 0;
	virtual void printSysConfig() = 0;
	virtual const CommonInfo& getCommonInfo() const = 0;
	virtual const std::vector<HotKeyItemInfo>& getHotKeyInfo() const = 0;
	virtual int getLoggingLevel() const = 0;
	virtual const DebugInfo& getDebugInfo() const = 0;
	virtual const ChromiumInfo& getChromiumInfo() const = 0;
	virtual const Resafety::DeepWorld::EngineSettingConfig& getEngineSettingConfig() const = 0;
	virtual bool getResistReplayAttacks() = 0;
	virtual bool getUseRefreshToken() = 0;
	virtual bool getLoadNetResource() = 0;
	virtual bool getUseRcloneState() = 0;
	virtual int getSyncInterval() = 0;
	virtual int getEncryptionMode() = 0;
};