#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <Windows.h>

//=================================================================================================

class PalmReader
{
public:
	PalmReader();
	~PalmReader();
	void run();
	void stop();
	bool getStatus() const;

private:
	void handleInput();
	void processFrame(cv::Mat& frame);

	const std::string WINDOW_NAME = "Test Application";
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int WAITING_TIME = 33;

	cv::VideoCapture capture;
	bool isRunning;
};

