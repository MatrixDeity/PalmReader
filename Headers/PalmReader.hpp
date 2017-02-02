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
	bool isRunning() const;

private:
	const std::string WINDOW_NAME = "Palm Reader [v1.1]";
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int WAITING_TIME = 33;

	cv::VideoCapture capture;
	cv::CascadeClassifier classifier;
	bool running;

	void handleInput();
	void processFrame(cv::Mat& frame) const;
	void displayFrame(const cv::Mat& frame) const;
	void detectPalm(cv::Mat& frame);
};

