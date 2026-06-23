#include "locate.h"
#include <Windows.h>
#include <sstream>
#include <filesystem>
#include "../Utility.h"
#include "../../../thirdparty/rapidxml-1.13/rapidxml.hpp"
#include "../../../thirdparty/rapidxml-1.13/rapidxml_utils.hpp"

#define SuccessCode 0


std::wstring Utf8ToUCS2(const char* utf8, uint32_t srcLength)
{
	//int size = MultiByteToWideChar(CP_UTF8, 0, utf8, srcLength, NULL, srcLength);
	wchar_t* pwcsName = new wchar_t[srcLength+1];
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, (LPWSTR)pwcsName, srcLength );
	std::wstring result2(pwcsName, srcLength);
	delete[] pwcsName;
	return result2;
}

std::wstring Utf8ToUCS2(const char* utf8)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* pwcsName = new wchar_t[size + 1];
	MultiByteToWideChar(CP_UTF8, 0, utf8, size, (LPWSTR)pwcsName, size);
	std::wstring result2(pwcsName);
	delete[] pwcsName;
	return result2;
}

std::string UCS2ToUtf8(const wchar_t* gbk, uint32_t srcLength)
{
	char* pcsName = new char[srcLength + 1];
	WideCharToMultiByte(CP_UTF8, 0, gbk, -1, (LPSTR)pcsName, srcLength, 0, 0);
	std::string result2(pcsName, srcLength);
	delete[] pcsName;
	return result2;
}

std::string UCS2ToUtf8(const wchar_t* gbk)
{
	int size = WideCharToMultiByte(CP_UTF8, 0, gbk, -1, NULL, 0, 0, 0);
	char* pcsName = new char[size + 1];
	WideCharToMultiByte(CP_UTF8, 0, gbk, size, (LPSTR)pcsName, size, 0, 0);
	std::string result2(pcsName);
	delete[] pcsName;
	return result2;
}

namespace Resafety {
	namespace DeepEye
	{


		static resafetyLocate* g_interface = nullptr;

		resafetyLocate::resafetyLocate()
		{
	
		}

		resafetyLocate::~resafetyLocate()
		{
	
		}

		const std::string resafetyLocate::getCurrentLanguage()
		{
			return m_strLanguageCode;
		}

		const std::vector<std::string > & resafetyLocate::getLanguageList()
		{
			return m_languagesVecA;
		}

		std::vector<std::wstring> SplitStringT(
			std::wstring str,
			std::wstring delimiter) 
		{
			std::vector<std::wstring> result;
			if (str.empty())
				return result;

			size_t start = 0;
			while (start != std::wstring::npos) {
				size_t end = str.find_first_of(delimiter, start);

				std::wstring piece;
				if (end == std::wstring::npos) {
					piece = str.substr(start);
					start = std::wstring::npos;
				}
				else {
					piece = str.substr(start, end - start);
					start = end + 1;
				}

		
				if (!piece.empty())
					result.emplace_back(piece);
			}
			return result;
		}

		void resafetyLocate::detectLocate()
		{
			const ULONG call_flags = MUI_LANGUAGE_NAME;
			ULONG language_count = 0;
			ULONG buffer_length = 0;
			//if (!::GetSystemPreferredUILanguages(call_flags, &language_count, nullptr, &buffer_length) ||!buffer_length) 
			if (!::GetUserPreferredUILanguages(call_flags, &language_count, nullptr, &buffer_length) || !buffer_length)	
			{
				m_strLanguageCode = "en-US";
				return;
			}

			std::wstring buffer(buffer_length, '\0');
			//if (!::GetSystemPreferredUILanguages(call_flags, &language_count, PZZWSTR(buffer.data()), &buffer_length) || !language_count)
			if (!::GetUserPreferredUILanguages(call_flags, &language_count, PZZWSTR(buffer.data()), &buffer_length) || !language_count)	
			{
				m_strLanguageCode = "en-US";
				return;
			}

			for (auto token : SplitStringT(buffer, std::wstring( L"\0",1)))
			{
				std::string utf8Str = UCS2ToUtf8(token.data());
				m_languagesVecA.emplace_back(utf8Str.data());
			}
			//m_strLanguageCode = m_languagesVecA.empty()? "en-US" : m_languagesVecA.front() ;
		}

		void resafetyLocate::readLanguageAdaptedConfig(const std::string & languageConfigPath)
		{
			//std::string solutionPath = Resafety::DeepWorld::GetFramework()->getSolutionPath();
			
			std::string configPath = languageConfigPath ;
			//ParseTool::GetExePath(configPath);
			wchar_t szBuffer[MAX_PATH] = { 0 };

			std::wstring ucs2ConfigPath = Utf8ToUCS2(configPath.data());

			int languageNum = GetPrivateProfileIntW(L"language", L"num", 0, ucs2ConfigPath.data());
			memset(szBuffer, 0, MAX_PATH);

			DWORD dwCount = GetPrivateProfileStringW(L"language", L"forceLanguage", NULL, szBuffer, MAX_PATH, ucs2ConfigPath.data());
			if (dwCount > 0)
			{
				m_strForceLanguageCode = UCS2ToUtf8(szBuffer);
			}

			if (languageNum>0)
			{
				for (size_t i = 0; i < languageNum; i++)
				{
					std::wstring wKeyName = L"langName" + std::to_wstring(i);
					GetPrivateProfileStringW(L"language", wKeyName.c_str(), NULL, szBuffer, MAX_PATH, ucs2ConfigPath.data());
					std::string utf8Str = UCS2ToUtf8(szBuffer);
					m_languagesVecAdapted.emplace_back(utf8Str.data());
					memset(szBuffer, 0, MAX_PATH);
				}
			}
		}

		void resafetyLocate::readLanguageDesignated(const std::string& lang)
		{
			std::string configPath = m_binPath + u8"config/Language/"+ lang +"/lang_" + lang + u8".xml";
			std::experimental::filesystem::path configu8Path = std::experimental::filesystem::u8path(configPath);
			if (!std::experimental::filesystem::exists(configu8Path))
			{
				std::string outMessage = u8"语言包不存在:"+configPath;
				OutputDebugStringA(outMessage.c_str());
				//LogErrorEx(u8"语言包不存在:%s", configPath);
				return;
			}
			readLanguagePak(configPath);
		}

		resafetyLocate* resafetyLocate::GetLocateInterface()
		{
			if (g_interface == nullptr)
			{
				g_interface = new resafetyLocate();

			}
			return g_interface;
		}

		std::string resafetyLocate::mergeoutUILanguage()
		{
			std::string strLanguageCode = m_languagesVecA.front();
			auto iter = std::find(m_languagesVecAdapted.begin(), m_languagesVecAdapted.end(), strLanguageCode.c_str());
			if (iter == m_languagesVecAdapted.end())
			{
				strLanguageCode = "en-US";
			}
			return strLanguageCode;
		}

		void resafetyLocate::init(const std::string& binPath, const std::string& languageConfigPath)
		{
			m_languagesVecA.clear();
			m_languagesVecAdapted.clear();
			m_binPath = binPath;
			m_languageConfigPath = languageConfigPath;
			detectLocate();
			readLanguageAdaptedConfig(languageConfigPath);
			std::string language = mergeoutUILanguage();
			if (!m_strForceLanguageCode.empty())
				language = m_strForceLanguageCode;
			setLocateLanguage(language);
		}

		void resafetyLocate::setLocateLanguage(const std::string& lang)
		{
			m_messagePak.clear();
			m_strLanguageCode = lang;
			readLanguageDesignated(lang);
		}

		std::string resafetyLocate::getMessage(const std::string& messageid)
		{
			auto iter = m_messagePak.find(messageid);
			std::string res = iter == m_messagePak.end() ? "" : iter->second.m_value;
			return res;
		}

		std::string resafetyLocate::getConfigPath()
		{
			return m_languageConfigPath;
		}

		void resafetyLocate::readLanguagePak(const std::string& lang)
		{
			std::experimental::filesystem::path configu8Path = std::experimental::filesystem::u8path(lang);

			// Open stream
			std::basic_ifstream<char> stream(configu8Path, std::ios::binary);
			rapidxml::xml_document<> doc;
			rapidxml::file<> fdoc(stream);
			stream.close();
			doc.parse<0>(fdoc.data());
			rapidxml::xml_node<>* langNode = doc.first_node("lang");
			rapidxml::xml_node<>* messagesNode = nullptr;
			int messageCount = 0;
			if (langNode)
			{
				messagesNode = langNode->first_node("messages");
				if (messagesNode)
				{
					rapidxml::xml_attribute<>* messagesCountAttribute = messagesNode->first_attribute("listSize");
					if (messagesCountAttribute)
					{
						messageCount = atoi(messagesCountAttribute->value());
					}
				}
			}
			for (size_t messageNum = 0; messageNum < messageCount;++messageNum)
			{
				languageMessage messageTemp;
				std::string messageNodeName = "message_"+std::to_string(messageNum);
				rapidxml::xml_node<>* message_Node = messagesNode->first_node(messageNodeName.c_str());
				if (message_Node)
				{
					rapidxml::xml_attribute<>* messageIDAttr = message_Node->first_attribute("id");
					if (!messageIDAttr)
					{
						continue;
					}
					messageTemp.m_id = messageIDAttr->value();
					rapidxml::xml_attribute<>* messageDesAttr = message_Node->first_attribute("desc");
					if (messageDesAttr)
					{
						messageTemp.m_des = messageDesAttr->value();
					}
					messageTemp.m_value = message_Node->value();
					m_messagePak.insert(std::make_pair(messageTemp.m_id, messageTemp));
				}
			}
		}

	}
}



