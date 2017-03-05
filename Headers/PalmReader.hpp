#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <Windows.h>

#include "Detector.hpp"

//=================================================================================================

class PalmReader
{
public:
	PalmReader();
	~PalmReader();
	void run();
	void stop();
	bool isRunning() const;

private:
	const std::string WINDOW_NAME = "Palm Reader [v2.0]";
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int WAITING_TIME = 33;
	const int IDLE_FRAMES = 300;

	cv::VideoCapture capture;
	Detector detector;
	bool running;

	void handleInput();
	void processFrame(cv::Mat& frame);
	void displayFrame(const cv::Mat& frame) const;
	void prepareNegative(const cv::Mat& frame, cv::Mat& negative);
};

