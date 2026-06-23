#include "../CyberUniverseApi/StringTool.h"
#include <tchar.h>
#include <windows.h>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <xstring>

using namespace std;

namespace Resafety {
	namespace CyberUniverseStudio {
		bool StringTool::StringCmpIgnoreCase(std::string str1, std::string str2)
		{
			std::transform(str1.begin(), str1.end(), str1.begin(), towupper);
			std::transform(str2.begin(), str2.end(), str2.begin(), towupper);
			return (str1 == str2);
		}

		void StringTool::StringReplace(std::string& src, const std::string& replacethis, const std::string& withthis)
		{
			std::string::size_type pos = src.find(replacethis);
			std::string::size_type replacethisLen = replacethis.size();
			std::string::size_type withthisLen = withthis.size();
			if (replacethisLen == 0)
				return;
			while (pos != std::string::npos)
			{
				src.replace(pos, replacethisLen, withthis);
				pos = src.find(replacethis, pos + withthisLen);
			}
		}

		std::string StringTool::Utf8ToGbk(const char* utf8)
		{
			if (!utf8)
				return "";
			wchar_t* widechar = NULL;
			char* multibyte = NULL;
			int length = 0;
			length = ::MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
			if (length <= 0)
				return "";
			widechar = new wchar_t[length];
			::MultiByteToWideChar(CP_UTF8, 0, utf8, -1, widechar, length);
			length = ::WideCharToMultiByte(CP_ACP, 0, widechar, -1, NULL, 0, NULL, NULL);
			if (length <= 0)
			{
				delete[] widechar;
				return "";
			}
			multibyte = new char[length];
			::WideCharToMultiByte(CP_ACP, 0, widechar, -1, multibyte, length, NULL, NULL);
			delete[] widechar;
			std::string gbk(multibyte);
			delete[] multibyte;
			return gbk;
		}

		std::string StringTool::GbkToUtf8(const char* gbk)
		{
			if (!gbk)
				return "";
			wchar_t* widechar = NULL;
			char* multibyte = NULL;
			int length = 0;
			length = ::MultiByteToWideChar(CP_ACP, 0, gbk, -1, NULL, 0);
			if (length <= 0)
				return "";
			widechar = new wchar_t[length];
			::MultiByteToWideChar(CP_ACP, 0, gbk, -1, widechar, length);
			length = ::WideCharToMultiByte(CP_UTF8, 0, widechar, -1, NULL, 0, NULL, NULL);
			if (length <= 0)
			{
				delete[] widechar;
				return "";
			}
			multibyte = new char[length];
			::WideCharToMultiByte(CP_UTF8, 0, widechar, -1, multibyte, length, NULL, NULL);
			delete[] widechar;
			std::string utf8(multibyte);
			delete[] multibyte;
			return utf8;
		}

		bool StringTool::IsUTF8(const char* str)
		{
			unsigned int nBytes = 0;
			//UFT8可用1-6个字节编码,ASCII用一个字节

			unsigned char chr = *str;
			bool bAllAscii = true;
			for (unsigned int i = 0; str[i] != '\0'; ++i) {
				chr = *(str + i);
				//判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx

				if (nBytes == 0 && (chr & 0x80) != 0) {
					bAllAscii = false;
				}
				if (nBytes == 0) {
					//如果不是ASCII码,应该是多字节符,计算字节数

					if (chr >= 0x80) {
						if (chr >= 0xFC && chr <= 0xFD) {
							nBytes = 6;
						}
						else if (chr >= 0xF8) {
							nBytes = 5;
						}
						else if (chr >= 0xF0) {
							nBytes = 4;
						}
						else if (chr >= 0xE0) {
							nBytes = 3;
						}
						else if (chr >= 0xC0) {
							nBytes = 2;
						}
						else {
							return false;
						}
						nBytes--;
					}
				}
				else {
					//多字节符的非首字节,应为 10xxxxxx

					if ((chr & 0xC0) != 0x80) {
						return false;
					}
					//减到为零为止
					nBytes--;
				}
			}
			//违返UTF8编码规则

			if (nBytes != 0) {
				return false;
			}
			if (bAllAscii) {
				//如果全部都是ASCII, 也是UTF8

				return true;
			}
			return true;
		}

		std::wstring StringTool::MbToWc(const std::string& multi_byte)
		{
			std::wstring widechar;
			if (multi_byte.empty())
				return widechar;
			int length = ::MultiByteToWideChar(CP_ACP, 0, multi_byte.c_str(), -1, NULL, 0);
			if (length <= 0)
				return widechar;
			widechar.resize(length);
			::MultiByteToWideChar(CP_ACP, 0, multi_byte.c_str(), -1, (LPWSTR)widechar.c_str(), length);
			return widechar;
		}

		std::string StringTool::WcToMb(const std::wstring& wide_char)
		{
			std::string multibyte;
			if (wide_char.empty())
				return multibyte;
			int length = ::WideCharToMultiByte(CP_ACP, 0, wide_char.c_str(), -1, NULL, 0, NULL, NULL);
			if (length <= 0)
				return multibyte;
			multibyte.resize(length);
			::WideCharToMultiByte(CP_ACP, 0, wide_char.c_str(), -1, (LPSTR)multibyte.c_str(), length, NULL, NULL);
			return multibyte;
		}

		std::string StringTool::UrlEncode(const std::string& src)
		{
			char const* inStr = src.c_str();
			size_t inStrLen = strlen(inStr);
			size_t outStrLen = 0;
			std::string outStr;
			register unsigned char c;
			unsigned char* to, * start;
			unsigned char const* from, * end;
			unsigned char hexchars[] = "0123456789ABCDEF";
			from = (unsigned char*)inStr;
			end = (unsigned char*)inStr + inStrLen;
			start = to = (unsigned char*)malloc(3 * inStrLen + 1);

			while (from < end)
			{
				c = *from++;
				if ((c < '0' && c != '-' && c != '.' && c != '/')
					|| (c < 'A' && c > '9')
					|| (c > 'Z' && c < 'a' && c != '_' && c != '\\')
					|| (c > 'z'))
				{
					to[0] = '%';
					to[1] = hexchars[c >> 4];
					to[2] = hexchars[c & 15];
					to += 3;
				}
				else
				{
					*to++ = c;
				}
			}
			*to = 0;
			outStrLen = to - start;
			outStr = (char*)start;
			free(start);
			return outStr;
		}

		std::string StringTool::UrlDecode(const std::string& src)
		{
			std::string out = src;
			int inStrLen = (int)out.length();
			char* dest = &out[0];
			char* data = dest;

			while (inStrLen--)
			{
				if (*data == '+')
				{
					*dest = ' ';
				}
				else if (*data == '%' && inStrLen >= 2 && isxdigit((int)*(data + 1)) && isxdigit((int)*(data + 2)))
				{
					++data;
					int c = *(unsigned char*)data;
					if (isupper(c))
						c = tolower(c);
					int value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

					++data;
					c = *(unsigned char*)data;
					if (isupper(c))
						c = tolower(c);
					value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

					*dest = (char)value;
					inStrLen -= 2;
				}
				else
				{
					*dest = *data;
				}
				++data;
				++dest;
			}
			*dest = '\0';
			return out;
		}

		std::string StringTool::LowerStr(const std::string& src)
		{
			std::string lower(src);
			std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
			return lower;
		}

		std::string StringTool::UpperStr(const std::string& src)
		{
			std::string upper(src);
			std::transform(upper.begin(), upper.end(), upper.begin(), ::tolower);
			return upper;
		}

		void StringTool::Trim(std::string& src)
		{
			if (!src.empty())
			{
				src.erase(0, src.find_first_not_of(" \t"));
				src.erase(src.find_last_not_of(" \t") + 1);
			}
		}

		std::string StringTool::Format(const char* format, ...)
		{
			std::string ret;
			va_list ap;
			va_start(ap, format);
			char* buf = (char*)malloc(1024 * 100);
			if (buf != nullptr)
			{
				vsnprintf(buf, 1024 * 100, format, ap);
				ret = buf;
				free(buf);
			}
			va_end(ap);
			return ret;
		}

		std::vector<std::string> StringTool::Split(const std::string& src, const std::string& sep)
		{
			std::vector<std::string> strVec;
			std::string::size_type linepos = 0;
			std::string::size_type endpos = 0;
			while (endpos != std::string::npos)
			{
				endpos = src.find_first_of(sep, linepos);
				strVec.push_back(src.substr(linepos, endpos - linepos));
				linepos = endpos + 1;
			}
			return strVec;
		}

		bool StringTool::SplitOnce(const std::string& src, const std::string& sep, std::string& strLeft, std::string& strRight)
		{
			size_t pos = src.find(sep);
			if (pos != std::string::npos)
			{
				strLeft = std::string(src, 0, pos);
				strRight = std::string(src, pos + 1);
				Trim(strLeft);
				Trim(strRight);
				return true;
			}
			else
			{
				strLeft = src;
				Trim(strLeft);
				strRight = "";
				return false;
			}
			return false;
		}

		std::string StringTool::getTimeString()
		{
			std::time_t t = std::time(nullptr);
			std::tm tm;
			localtime_s(&tm, &t);
			std::ostringstream oss;
			oss << std::put_time(&tm, "%F %T");
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) % 1000;
			std::string strMs = std::to_string(ms.count());
			while (strMs.size() < 3)
			{
				strMs.insert(0, "0");
			}
			std::string str = oss.str() + "." + strMs;
			return str;
		}

		uint64_t StringTool::getCurTime()
		{
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			return ms.count();
		}

		string StringTool::Base64Encode(const unsigned char* Data, int DataByte)
		{
			//编码表
			const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			//返回值
			std::string strEncode;
			unsigned char Tmp[4] = { 0 };
			int LineLength = 0;
			for (int i = 0; i < (int)(DataByte / 3); i++)
			{
				Tmp[1] = *Data++;
				Tmp[2] = *Data++;
				Tmp[3] = *Data++;
				strEncode += EncodeTable[Tmp[1] >> 2];
				strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
				strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
				strEncode += EncodeTable[Tmp[3] & 0x3F];
				if (LineLength += 4, LineLength == 76) { strEncode += "\r\n"; LineLength = 0; }
			}
			//对剩余数据进行编码
			int Mod = DataByte % 3;
			if (Mod == 1)
			{
				Tmp[1] = *Data++;
				strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
				strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
				strEncode += "==";
			}
			else if (Mod == 2)
			{
				Tmp[1] = *Data++;
				Tmp[2] = *Data++;
				strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
				strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
				strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
				strEncode += "=";
			}

			return strEncode;
		}

		string StringTool::Base64Decode(const char* Data, int DataByte, int& OutByte)
		{
			//解码表
			const char DecodeTable[] =
			{
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				62, // '+'
				0, 0, 0,
				63, // '/'
				52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
				0, 0, 0, 0, 0, 0, 0,
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
				13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
				0, 0, 0, 0, 0, 0,
				26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
				39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 // 'a'-'z'
			};
			//返回值
			std::string strDecode;
			int nValue;
			int i = 0;
			while (i < DataByte)
			{
				if (*Data != '\r' && *Data != '\n')
				{
					nValue = DecodeTable[*Data++] << 18;
					nValue += DecodeTable[*Data++] << 12;
					strDecode += (nValue & 0x00FF0000) >> 16;
					OutByte++;
					if (*Data != '=')
					{
						nValue += DecodeTable[*Data++] << 6;
						strDecode += (nValue & 0x0000FF00) >> 8;
						OutByte++;
						if (*Data != '=')
						{
							nValue += DecodeTable[*Data++];
							strDecode += nValue & 0x000000FF;
							OutByte++;
						}
					}
					i += 4;
				}
				else// 回车换行,跳过
				{
					Data++;
					i++;
				}
			}
			return strDecode;
		}

		std::wstring StringTool::utfString2WString(const std::string& str)
		{

			int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
			wchar_t* pwcsName = new wchar_t[size];
			MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pwcsName, size);
			std::wstring result2(pwcsName);
			delete[] pwcsName;
			return result2;
		}

		std::string StringTool::WString2utfString(const std::wstring& str)
		{
			int size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
			char* pwcsName = new char[size];
			WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, (LPSTR)pwcsName, size, NULL, NULL);
			std::string result2(pwcsName);
			delete[] pwcsName;
			return result2;
		}

		std::string StringTool::ACPWString2String(const std::wstring& str)
		{
			int size = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
			char* pwcsName = new char[size];
			WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, (LPSTR)pwcsName, size, NULL, NULL);
			std::string result2(pwcsName);
			delete[] pwcsName;
			return result2;
		}
	}
}