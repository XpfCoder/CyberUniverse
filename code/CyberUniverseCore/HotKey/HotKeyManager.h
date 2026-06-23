#pragma once
#include<map>
#include<vector>
#include <unordered_map>
#include "HotKeyItemInfo.h"
#include "../CyberUniverseApi/LogManagerInterface.h"
#include "../CyberUniverseApi/HotKeyManagerInterface.h"

namespace Resafety {
	namespace CyberUniverseStudio {
		struct HotKeyInfo
		{
			uint32_t m_mainKey{ 0 };
			bool m_ctrl;
			bool m_shift;
			bool m_alt;

			HotKeyInfo(uint32_t mainKey, bool ctrl, bool shift, bool alt)
			{
				m_mainKey = mainKey;
				m_ctrl = ctrl;
				m_shift = shift;
				m_alt = alt;
			}
			bool operator==(const HotKeyInfo& hotKeyInfo) const
			{
				if (m_mainKey == hotKeyInfo.m_mainKey && m_ctrl == hotKeyInfo.m_ctrl && m_shift == hotKeyInfo.m_shift && m_alt == hotKeyInfo.m_alt)
					return true;
				return false;
			}
			bool operator<(const HotKeyInfo& hotKeyInfo) const
			{
				if (m_mainKey != hotKeyInfo.m_mainKey)
				{
					return m_mainKey < hotKeyInfo.m_mainKey;
				}
				if (m_ctrl != hotKeyInfo.m_ctrl)
				{
					return m_ctrl < hotKeyInfo.m_ctrl;
				}
				if (m_alt != hotKeyInfo.m_alt)
				{
					return m_alt < hotKeyInfo.m_alt;
				}
				if (m_shift != hotKeyInfo.m_shift)
				{
					return m_shift < hotKeyInfo.m_shift;
				}
				return false;
			}
			HotKeyInfo(const std::string& hotKeyInfo);
			bool isValid() const;
		};

		class HotKeyManager :public IHotKeyManager
		{
		public:
			virtual void execute(uint32_t mainKey, bool ctrl, bool shift, bool alt) override;
			virtual bool registerHotKey(const std::string& hotKeyName, IHotKey* hotkey) override;
			virtual bool unregisterHotKey(const std::string& hotKeyName) override;
			virtual bool bindHotKeyInfo(const std::string& hotKeyName, const std::string& hotKeyInfo) override;
			virtual bool unbindHotKeyInfo(const std::string& hotKeyInfo) override;
			//void init(const std::vector<HotKeyItemInfo>& hotKeyList);
		private:
			IHotKey* getHotKeyByName(const std::string& hotKeyName) const;
			std::map<HotKeyInfo, std::string> m_hotKeys;
			std::unordered_map <std::string, IHotKey*> m_hotKeyMap;
		};

	}
}