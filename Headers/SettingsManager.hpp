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

		int idleFrames;
		int palmSize;
		int historyLength;
		float thresholdRate;
		double learningRate;

		int waitingTime;

		SettingsManager(const std::string& pathToExe) :
			path(pathToExe.substr(0, pathToExe.find_last_of("\\")) + "\\settings.ini")
		{
			reloadSettings();
		}

		void reloadSettings()
		{
			std::string section = "Window";
			loadSetting(section, "windowName", windowName);
			loadSetting(section, "windowWidth", windowWidth);
			loadSetting(section, "windowHeight", windowHeight);

			section = "Detector";
			loadSetting(section, "idleFrames", idleFrames);
			loadSetting(section, "palmSize", palmSize);
			loadSetting(section, "historyLength", historyLength);
			loadSetting(section, "thresholdRate", thresholdRate);
			loadSetting(section, "learningRate", learningRate);

			section = "Other";
			loadSetting(section, "waitingTime", waitingTime);
		}

	private:
		static const int MAX_CONTENT_SIZE = 256;

		std::string path;

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
			setting.append(str);
		}
	};
}