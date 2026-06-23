//#include <string>
//#include <fstream>
//#include <algorithm>
//#include "HotKeyManager.h"
//#include "DeepEyeCore/Platform/Keyboard.h"
//#include "../CyberUniverseApi/StringTool.h"
//
//static const std::map<std::string, Resafety::DeepEye::Keyboard::Key> StringKeyboardMap =
//{
//	{ "BACK", Resafety::DeepEye::Keyboard::key_back },
//	{ "TAB" , Resafety::DeepEye::Keyboard::key_tab },
//	{ "RETURN" , Resafety::DeepEye::Keyboard::key_return },
//	{ "PAUSE" , Resafety::DeepEye::Keyboard::key_pause },
//	{ "CAPITAL" , Resafety::DeepEye::Keyboard::key_capital },
//	{ "KANA" , Resafety::DeepEye::Keyboard::key_kana },
//	{ "KANJI" , Resafety::DeepEye::Keyboard::key_kanji },
//	{ "ESCAPE" , Resafety::DeepEye::Keyboard::key_escape },
//	{ "CONVERT" , Resafety::DeepEye::Keyboard::key_convert },
//	{ "NONCONVERT" , Resafety::DeepEye::Keyboard::key_noconvert },
//	{ "SPACE" , Resafety::DeepEye::Keyboard::key_space },
//	{ "PRIOR" , Resafety::DeepEye::Keyboard::key_prior },
//	{ "NEXT" , Resafety::DeepEye::Keyboard::key_next },
//	{ "END" , Resafety::DeepEye::Keyboard::key_end },
//	{ "HOME" , Resafety::DeepEye::Keyboard::key_home },
//	{ "LEFT" , Resafety::DeepEye::Keyboard::key_left },
//	{ "UP" , Resafety::DeepEye::Keyboard::key_up },
//	{ "RIGHT" , Resafety::DeepEye::Keyboard::key_right },
//	{ "DOWN" , Resafety::DeepEye::Keyboard::key_down },
//	{ "SNAPSHOT" , Resafety::DeepEye::Keyboard::key_sysrq },
//	{ "INSERT" , Resafety::DeepEye::Keyboard::key_insert },
//	{ "DELETE" , Resafety::DeepEye::Keyboard::key_delete },
//	{ "0" , Resafety::DeepEye::Keyboard::key_0 },
//	{ "1" , Resafety::DeepEye::Keyboard::key_1 },
//	{ "2" , Resafety::DeepEye::Keyboard::key_2 },
//	{ "3" , Resafety::DeepEye::Keyboard::key_3 },
//	{ "4" , Resafety::DeepEye::Keyboard::key_4 },
//	{ "5" , Resafety::DeepEye::Keyboard::key_5 },
//	{ "6" , Resafety::DeepEye::Keyboard::key_6 },
//	{ "7" , Resafety::DeepEye::Keyboard::key_7 },
//	{ "8" , Resafety::DeepEye::Keyboard::key_8 },
//	{ "9" , Resafety::DeepEye::Keyboard::key_9 },
//	{ "A" , Resafety::DeepEye::Keyboard::key_a },
//	{ "B" , Resafety::DeepEye::Keyboard::key_b },
//	{ "C" , Resafety::DeepEye::Keyboard::key_c },
//	{ "D" , Resafety::DeepEye::Keyboard::key_d },
//	{ "E" , Resafety::DeepEye::Keyboard::key_e },
//	{ "F" , Resafety::DeepEye::Keyboard::key_f },
//	{ "G" , Resafety::DeepEye::Keyboard::key_g },
//	{ "H" , Resafety::DeepEye::Keyboard::key_h },
//	{ "I" , Resafety::DeepEye::Keyboard::key_i },
//	{ "J" , Resafety::DeepEye::Keyboard::key_j },
//	{ "K" , Resafety::DeepEye::Keyboard::key_k },
//	{ "L" , Resafety::DeepEye::Keyboard::key_l },
//	{ "M" , Resafety::DeepEye::Keyboard::key_m },
//	{ "N" , Resafety::DeepEye::Keyboard::key_n },
//	{ "O" , Resafety::DeepEye::Keyboard::key_o },
//	{ "P" , Resafety::DeepEye::Keyboard::key_p },
//	{ "Q" , Resafety::DeepEye::Keyboard::key_q },
//	{ "R" , Resafety::DeepEye::Keyboard::key_r },
//	{ "S" , Resafety::DeepEye::Keyboard::key_s },
//	{ "T" , Resafety::DeepEye::Keyboard::key_t },
//	{ "U" , Resafety::DeepEye::Keyboard::key_u },
//	{ "V" , Resafety::DeepEye::Keyboard::key_v },
//	{ "W" , Resafety::DeepEye::Keyboard::key_w },
//	{ "X" , Resafety::DeepEye::Keyboard::key_x },
//	{ "Y" , Resafety::DeepEye::Keyboard::key_y },
//	{ "Z" , Resafety::DeepEye::Keyboard::key_z },
//	{ "LWIN" , Resafety::DeepEye::Keyboard::key_lwin },
//	{ "RWIN" , Resafety::DeepEye::Keyboard::key_rwin },
//	{ "APPS" , Resafety::DeepEye::Keyboard::key_apps },
//	{ "SLEEP" , Resafety::DeepEye::Keyboard::key_sleep },
//	{ "NUMPAD0" , Resafety::DeepEye::Keyboard::key_numpad0 },
//	{ "NUMPAD1" , Resafety::DeepEye::Keyboard::key_numpad1 },
//	{ "NUMPAD2" , Resafety::DeepEye::Keyboard::key_numpad2 },
//	{ "NUMPAD3" , Resafety::DeepEye::Keyboard::key_numpad3 },
//	{ "NUMPAD4" , Resafety::DeepEye::Keyboard::key_numpad4 },
//	{ "NUMPAD5" , Resafety::DeepEye::Keyboard::key_numpad5 },
//	{ "NUMPAD6" , Resafety::DeepEye::Keyboard::key_numpad6 },
//	{ "NUMPAD7" , Resafety::DeepEye::Keyboard::key_numpad7 },
//	{ "NUMPAD8" , Resafety::DeepEye::Keyboard::key_numpad8 },
//	{ "NUMPAD9" , Resafety::DeepEye::Keyboard::key_numpad9 },
//	{ "MULTIPLY" , Resafety::DeepEye::Keyboard::key_multiply },
//	{ "ADD" , Resafety::DeepEye::Keyboard::key_add },
//	{ "SUBTRACT" , Resafety::DeepEye::Keyboard::key_subtract },
//	{ "DECIMAL" , Resafety::DeepEye::Keyboard::key_decimal },
//	{ "DIVIDE" , Resafety::DeepEye::Keyboard::key_divide },
//	{ "F1" , Resafety::DeepEye::Keyboard::key_f1 },
//	{ "F2" , Resafety::DeepEye::Keyboard::key_f2 },
//	{ "F3" , Resafety::DeepEye::Keyboard::key_f3 },
//	{ "F4" , Resafety::DeepEye::Keyboard::key_f4 },
//	{ "F5" , Resafety::DeepEye::Keyboard::key_f5 },
//	{ "F6" , Resafety::DeepEye::Keyboard::key_f6 },
//	{ "F7" , Resafety::DeepEye::Keyboard::key_f7 },
//	{ "F8" , Resafety::DeepEye::Keyboard::key_f8 },
//	{ "F9" , Resafety::DeepEye::Keyboard::key_f9 },
//	{ "F10" , Resafety::DeepEye::Keyboard::key_f10 },
//	{ "F11" , Resafety::DeepEye::Keyboard::key_f11 },
//	{ "F12" , Resafety::DeepEye::Keyboard::key_f12 },
//	{ "F13" , Resafety::DeepEye::Keyboard::key_f13 },
//	{ "F14" , Resafety::DeepEye::Keyboard::key_f14 },
//	{ "F15" , Resafety::DeepEye::Keyboard::key_f15 },
//	{ "NUMLOCK" , Resafety::DeepEye::Keyboard::key_numlock },
//	{ "SCROLL" , Resafety::DeepEye::Keyboard::key_scroll },
////	{ "LSHIFT" , Resafety::DeepEye::Keyboard::key_lshift },
////	{ "RSHIFT" , Resafety::DeepEye::Keyboard::key_rshift },
////	{ "LCONTROL" , Resafety::DeepEye::Keyboard::key_lcontrol },
////	{ "RCONTROL" , Resafety::DeepEye::Keyboard::key_rcontrol },
////	{ "LMENU" , Resafety::DeepEye::Keyboard::key_lmenu },
////	{ "RMENU" , Resafety::DeepEye::Keyboard::key_rmenu },
//	{ "LBUTTON" , Resafety::DeepEye::Keyboard::key_lbutton },
//	{ "MBUTTON" , Resafety::DeepEye::Keyboard::key_mbutton },
//	{ "RBUTTON" , Resafety::DeepEye::Keyboard::key_rbutton },
//};
//namespace Resafety {
//	namespace CyberUniverseStudio {
//		bool HotKeyInfo::isValid() const
//		{
//			if (m_mainKey > 0 && Resafety::DeepEye::Keyboard::Key::key_rshift != m_mainKey
//				&& Resafety::DeepEye::Keyboard::Key::key_lshift != m_mainKey
//				&& Resafety::DeepEye::Keyboard::Key::key_lmenu != m_mainKey
//				&& Resafety::DeepEye::Keyboard::Key::key_rmenu != m_mainKey
//				&& Resafety::DeepEye::Keyboard::Key::key_lcontrol != m_mainKey
//				&& Resafety::DeepEye::Keyboard::Key::key_rcontrol != m_mainKey
//				&& m_mainKey <= 0xF0)
//				return true;
//			return false;
//		}
//
//		HotKeyInfo::HotKeyInfo(const std::string& hotKeyString)
//		{
//			m_mainKey = 0;
//			m_ctrl = false;
//			m_alt = false;
//			m_shift = false;
//			std::vector<std::string> subStringList = StringTool::Split(hotKeyString, "+");
//			for (size_t i = 0; i < subStringList.size(); i++)
//			{
//				StringTool::Trim(subStringList[i]);
//				transform(subStringList[i].begin(), subStringList[i].end(), subStringList[i].begin(), toupper);
//				if (subStringList[i] == "CTRL")
//				{
//					m_ctrl = true;
//				}
//				else if (subStringList[i] == "SHIFT")
//				{
//					m_shift = true;
//				}
//				else if (subStringList[i] == "ALT")
//				{
//					m_alt = true;
//				}
//				else
//				{
//					auto it = StringKeyboardMap.find(subStringList[i]);
//					if (it == StringKeyboardMap.end())
//					{
//						return;
//					}
//					if (m_mainKey != 0)
//					{
//						m_mainKey = 0;
//						return;
//					}
//					m_mainKey = (uint32_t)it->second;
//				}
//			}
//		}
//
//		//void HotKeyManager::init(const std::vector<HotKeyItemInfo>& hotKeyList)
//		//{
//		//	for (size_t i = 0; i < hotKeyList.size(); i++)
//		//	{
//		//		registerHotKeyInfo(hotKeyList[i].name, hotKeyList[i].keyboardInfo);
//		//	}
//		//}
//
//		bool HotKeyManager::registerHotKey(const std::string& hotKeyName, IHotKey* hotKey)
//		{
//			if (hotKeyName.empty())
//			{
//				GetLogManager()->logError(u8"HotKeyManager::registerHotKey failed,快捷键名称不能为空。");
//				return false;
//			}
//			if (hotKey == nullptr)
//			{
//				GetLogManager()->logError(u8"HotKeyManager::registerHotKey failed,%s的实现类指针为空。", hotKeyName.c_str());
//				return false;
//			}
//			std::string upperHotkeyName(hotKeyName);
//			std::transform(hotKeyName.begin(), hotKeyName.end(), upperHotkeyName.begin(), ::toupper);
//			if (m_hotKeyMap.find(hotKeyName) != m_hotKeyMap.end())
//			{
//				GetLogManager()->logError(u8"HotKeyManager::registerHotKey failed,快捷键名称%s已存在。", hotKeyName.c_str());
//				return false;
//			}
//			m_hotKeyMap[upperHotkeyName] = hotKey;
//			return true;
//		}
//
//		void HotKeyManager::execute(uint32_t mainKey, bool ctrl, bool shift, bool alt)
//		{
//			HotKeyInfo info(mainKey, ctrl, shift, alt);
//			auto it = m_hotKeys.find(info);
//			if (it != m_hotKeys.end())
//			{
//				Resafety::DeepWorld::IHotKey* hotKey = getHotKeyByName(it->second);
//				if (hotKey)
//				{
//					hotKey->execute();
//				}
//			}
//		}
//
//		bool HotKeyManager::unregisterHotKey(const std::string& hotKeyName)
//		{
//			std::string upperHotkeyName(hotKeyName);
//			std::transform(hotKeyName.begin(), hotKeyName.end(), upperHotkeyName.begin(), ::toupper);
//			auto it = m_hotKeyMap.find(upperHotkeyName);
//			if (it == m_hotKeyMap.end())
//			{
//				GetLogManager()->logError(u8"HotKeyManager::unregisterHotKey 失败，%s不存在", hotKeyName.c_str());
//				return false;
//			}
//			m_hotKeyMap.erase(hotKeyName);
//			GetLogManager()->logStandard(u8"HotKeyManager::unregisterHotKey,快捷键【%s】反注册成功。", hotKeyName.c_str());
//			return true;
//		}
//
//		bool HotKeyManager::bindHotKeyInfo(const std::string& hotKeyName, const std::string& hotKeyInfo)
//		{
//			HotKeyInfo hotKey(hotKeyInfo);
//			if (!hotKey.isValid())
//			{
//				GetLogManager()->logWarning(u8"HotKeyManager::init,快捷键【%s=%s】设置失败，不符合快捷键的定义规则。", hotKeyName.c_str(), hotKeyInfo.c_str());
//				return false;
//			}
//			auto it = m_hotKeys.find(hotKeyInfo);
//			if (it != m_hotKeys.end())
//			{
//				GetLogManager()->logError(u8"HotKeyManager::init,快捷键【%s=%s】设置失败，检测到重复的快捷键。", hotKeyName.c_str(), hotKeyInfo.c_str());
//				return false;
//			}
//			m_hotKeys.insert(std::make_pair(hotKeyInfo, hotKeyName));
//			GetLogManager()->logStandard(u8"HotKeyManager::init,快捷键【%s=%s】设置成功。", hotKeyName.c_str(), hotKeyInfo.c_str());
//			return true;
//		}
//
//		bool HotKeyManager::unbindHotKeyInfo(const std::string& hotKeyInfo)
//		{
//			HotKeyInfo hotKey(hotKeyInfo);
//			if (!hotKey.isValid())
//			{
//				GetLogManager()->logWarning(u8"HotKeyManager::unregisterHotKeyInfo,快捷键【%s】解除绑定失败，不符合快捷键的定义规则。", hotKeyInfo.c_str());
//				return false;
//			}
//			auto it = m_hotKeys.find(hotKeyInfo);
//			if (it == m_hotKeys.end())
//			{
//				GetLogManager()->logWarning(u8"HotKeyManager::unregisterHotKeyInfo,快捷键【%s】不存在，解除绑定失败。", hotKeyInfo.c_str());
//				return false;
//			}
//			GetLogManager()->logStandard(u8"HotKeyManager::unbindHotKeyInfo,快捷键【%s=%s】解除绑定成功。", it->second.c_str(), hotKeyInfo.c_str());
//			m_hotKeys.erase(it);
//			return true;
//		}
//
//		IHotKey* HotKeyManager::getHotKeyByName(const std::string& hotKeyName) const
//		{
//			std::string upperHotkeyName(hotKeyName);
//			std::transform(hotKeyName.begin(), hotKeyName.end(), upperHotkeyName.begin(), ::toupper);
//			auto it = m_hotKeyMap.find(upperHotkeyName);
//			if (it != m_hotKeyMap.end())
//			{
//				return it->second;
//			}
//			GetLogManager()->logError(u8"HotKeyManager::getHotKeyByName failed,快捷键名称【%s】尚未注册。", hotKeyName.c_str());
//			return nullptr;
//		}
//	}
//}