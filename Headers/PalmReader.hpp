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
		PalmReader(const SettingsManager& settings);
		~PalmReader();
		void run();
		void stop();
		bool isRunning() const;

	private:
		pr::SettingsManager settings;
		cv::VideoCapture capture;
		pr::Detector detector;
		pr::Detector::Gesture lastGesture;
		cv::BackgroundSubtractorMOG2 subtractor;
		pr::CommandExecutor executor;
		bool running;
		bool pause;
		int frameOfLearning;

		void createCommands();
		void processFrame(cv::Mat& frame, cv::Mat& processedFrame) const;
		void applySubtractor(cv::Mat& frame);
		void buildContours(cv::Mat& frame, const cv::Mat& processedFrame);
		void processGesture();
		void displayFrame(const cv::Mat& frame) const;
		void handleInput();
		void switchPause();
		void print(const std::string& message) const;
		void showHelp() const;
		bool isLearned() const;
	};
}
