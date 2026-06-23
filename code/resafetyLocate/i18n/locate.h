#pragma once
#include "../Utility.h"
#include <string>

#include <thread>
#include <mutex>
#include <Windows.h>
#include <vector>
#include <map>

namespace Resafety {
	namespace DeepEye 
	{
		struct languageMessage
		{
			std::string m_id{ "" };
			std::string m_value{ "" };
			std::string m_des{ "" };
		};

		class RESAFRTYLOCATE_EXPORT resafetyLocate
		{
		public:
			~resafetyLocate();
			const std::string getCurrentLanguage();

			const std::vector<std::string >& getLanguageList();

			static resafetyLocate* GetLocateInterface();

			void init(const std::string& binPath, const std::string& languageConfigPath);

			void setLocateLanguage(const std::string& lang);

			std::string getMessage(const std::string& messageid);

			std::string getConfigPath();


		private:
			resafetyLocate();

			void detectLocate();

			void readLanguageAdaptedConfig(const std::string& languageConfigPath);

			void readLanguageDesignated(const std::string& lang);

			std::string mergeoutUILanguage();

			void readLanguagePak(const std::string& lang);

			//void readDefaultHttpConfig();


		private:

			std::vector<std::string > m_languagesVecA;
			std::vector<std::string > m_languagesVecAdapted;
			bool m_bUserVerificationCode = true;
			std::string m_strForceLanguageCode{ "" };
			std::string m_strLanguageCode{ "" };
			std::string m_binPath{ "" };
			std::string m_languageConfigPath{ "" };
			std::map<std::string, languageMessage> m_messagePak;

		};
	}
}





