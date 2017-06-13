#pragma once

#include <string>
#include <Windows.h>

//=================================================================================================

namespace pr
{
	class SettingsManager
	{
	public:
		std::string windowName;
		int windowWidth;
		int windowHeight;

		int learningFrames;
		double palmMinSize;
		int historyLength;
		float thresholdRate;
		double learningRate;
		double defectMinLength;

		int waitingTime;
		bool suspended;

		SettingsManager(const std::string& pathToExe) :
			path(pathToExe.substr(0, pathToExe.find_last_of("\\")).append("\\settings.ini"))
		{
			loadSettings();
		}

		~SettingsManager()
		{
		}

	private:
		static const int MAX_CONTENT_SIZE = 256;

		std::string path;

		void loadSettings()
		{
			std::string section = "Window";
			loadSetting(section, "windowName", windowName);
			loadSetting(section, "windowWidth", windowWidth);
			loadSetting(section, "windowHeight", windowHeight);

			section = "Recognition";
			loadSetting(section, "learningFrames", learningFrames);
			loadSetting(section, "palmMinSize", palmMinSize);
			loadSetting(section, "historyLength", historyLength);
			loadSetting(section, "thresholdRate", thresholdRate);
			loadSetting(section, "learningRate", learningRate);
			loadSetting(section, "defectMinLength", defectMinLength);

			section = "Other";
			loadSetting(section, "waitingTime", waitingTime);
			loadSetting(section, "suspended", suspended);
		}

		template <typename T>
		void loadSetting(const std::string& section, const std::string& key, T& setting)
		{
			char str[MAX_CONTENT_SIZE];
			std::stringstream ss;
			GetPrivateProfileStringA(section.c_str(), key.c_str(), "0", str,
				MAX_CONTENT_SIZE, path.c_str());
			ss << str;
			ss >> setting;
		}

		void loadSetting(const std::string& section, const std::string& key,
			std::string& setting)
		{
			char str[MAX_CONTENT_SIZE];
			GetPrivateProfileStringA(section.c_str(), key.c_str(), "0", str,
				MAX_CONTENT_SIZE, path.c_str());
			setting.assign(str);
		}
	};
}