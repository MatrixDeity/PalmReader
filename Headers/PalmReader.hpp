#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <Windows.h>

#include "SettingsManager.hpp"
#include "Detector.hpp"
#include "CommandExecutor.hpp"

//=================================================================================================

namespace pr
{
	class PalmReader
	{
	public:
		explicit PalmReader(const SettingsManager& settings);
		~PalmReader();
		void run();
		void stop();
		bool isRunning() const;

	private:
		const std::string WINDOW_NAME;
		const int WAITING_TIME;

		cv::VideoCapture capture;
		pr::Detector detector;
		pr::Detector::Gesture lastGesture;
		pr::CommandExecutor executor;
		bool running;
		bool pause;

		void createCommands();
		void processFrame(cv::Mat& frame, cv::Mat& processedFrame) const;
		void subtractBackground(cv::Mat& processedFrame);
		void buildContours(cv::Mat& frame, const cv::Mat& processedFrame);
		void processGesture();
		void displayFrame(const cv::Mat& frame) const;
		void handleInput();
		void switchPause();
		void print(const std::string& message) const;
		void showCommandsList() const;
		void showHelp() const;
	};
}
