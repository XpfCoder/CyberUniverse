#pragma once
#include<string>
namespace Resafety {
	namespace CyberUniverseStudio {
		struct HotKeyItemInfo
		{
			std::string name;
			std::string keyboardInfo;
			HotKeyItemInfo(std::string na, std::string key)
			{
				name = na;
				keyboardInfo = key;
			}
		};
	}
}
