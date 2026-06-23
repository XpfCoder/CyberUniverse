#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace Resafety {
	namespace CyberUniverseStudio {
		class __declspec(dllexport) StringTool
		{
		public:
			static bool StringCmpIgnoreCase(std::string str1, std::string str2);
			static void StringReplace(std::string& src, const std::string& replacethis, const std::string& withthis);
			static std::string Utf8ToGbk(const char* utf8);
			static std::string GbkToUtf8(const char* gbk);
			static bool IsUTF8(const char* str);
			static std::wstring MbToWc(const std::string& multi_byte);
			static std::string WcToMb(const std::wstring& wide_char);
			static std::string UrlEncode(const std::string& src);
			static std::string UrlDecode(const std::string& src);
			//转换为小写
			static std::string LowerStr(const std::string& src);
			//转换为大写
			static std::string UpperStr(const std::string& src);
			//去除字符串左右的空格
			static void Trim(std::string& src);
			//字符串格式化
			static std::string Format(const char* format, ...);
			//字符串切割
			static std::vector<std::string> Split(const std::string& src, const std::string& sep);
			//字符串切割:只切割第一个sep
			static bool SplitOnce(const std::string& src, const std::string& sep, std::string& strLeft, std::string& strRight);
			//获取时间戳
			static std::string getTimeString();
			//获取当前系统时间(精确到毫秒)  since from epoch
			static uint64_t getCurTime();
			//模板函数，转换为字符串
			template<typename T>
			static std::string ToString(const T& value)
			{
				std::ostringstream stream;
				stream << value;
				return stream.str();
			}
			//模板函数，转换自字符串，失败返回NULL
			template<typename T>
			static T FromString(const std::string& src)
			{
				T value;
				std::istringstream s;
				s.str(src);
				try
				{
					s >> value;
				}
				catch (std::exception& ex)
				{
					return NULL;
				}
				return value;
			}

			//base64编码 解码
			//编码 DataByte [in]输入的数据长度,以字节为单位
			std::string Base64Encode(const unsigned char* Data, int DataByte);
			//解码 DataByte [in]输入的数据长度,以字节为单位 OutByte [out]输出的数据长度,以字节为单位,请不要通过返回值计算 输出数据的长度
			std::string Base64Decode(const char* Data, int DataByte, int& OutByte);

			static std::wstring utfString2WString(const std::string& str);
			static std::string WString2utfString(const std::wstring& str);
			static std::string ACPWString2String(const std::wstring& str);


		};
	}
}
