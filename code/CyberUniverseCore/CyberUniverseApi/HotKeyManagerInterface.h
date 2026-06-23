#pragma once
#include<string>

namespace Resafety {
	namespace CyberUniverseStudio {
		class IHotKey;
		class IHotKeyManager
		{
		public:
			virtual ~IHotKeyManager() {}
			virtual void execute(uint32_t mainKey, bool ctrl, bool shift, bool alt) = 0;
			virtual bool registerHotKey(const std::string& hotKeyName, IHotKey* hotkey) = 0;
			virtual bool unregisterHotKey(const std::string& hotKeyName) = 0;
			virtual bool bindHotKeyInfo(const std::string& hotKeyName, const std::string& hotKeyInfo) = 0;
			virtual bool unbindHotKeyInfo(const std::string& hotKeyInfo) = 0;
		};
		__declspec(dllexport) IHotKeyManager* GetHotKeyManager();
	}
}
