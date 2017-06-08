#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <Windows.h>

#include "SettingsManager.hpp"
#include "Detector.hpp"

//=================================================================================================

namespace pr
{
	class PalmReader
	{
	public:
		PalmReader(SettingsManager& settings);
		~PalmReader();
		void run();
		void stop();
		bool isRunning() const;

	private:
		pr::SettingsManager settings;
		cv::VideoCapture capture;
		pr::Detector detector;
		cv::BackgroundSubtractorMOG2 subtractor;
		bool running;
		bool learned;
		bool pause;

		void processFrame(cv::Mat& frame, cv::Mat& processedFrame);
		void applySubtractor(cv::Mat& frame);
		void buildContours(cv::Mat& frame, const cv::Mat& processedFrame);
		void displayFrame(const cv::Mat& frame) const;
		void handleInput();
		void switchPause();
	};
}
