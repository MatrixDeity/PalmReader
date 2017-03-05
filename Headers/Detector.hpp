#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

//=================================================================================================

class Detector
{
public:
	Detector(int history);
	~Detector();
	void subtractBackground(cv::Mat& frame);
	void drawContours(cv::Mat& frame);

private:
	cv::BackgroundSubtractorMOG2 subtractor;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> hull;
	std::vector<cv::Vec4i> hierarchy;
	int historySize;
};

