#include "Detector.hpp"

//=================================================================================================

Detector::Detector(int history) :
	subtractor(history, 16.0F),
	contours(),
	hull(),
	hierarchy(),
	historySize(history)
{
}

//=================================================================================================

Detector::~Detector()
{
}

//=================================================================================================

void Detector::subtractBackground(cv::Mat& frame)
{
	subtractor(frame, frame);
}

//=================================================================================================

void Detector::drawContour(cv::Mat& frame)
{
	/*
	std::vector<std::vector<cv::Point>> contours, hull;
	std::vector<cv::Vec4i> hierarchy;
	findContours(frame, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE,
	cv::Point(0, 0));

	hull.resize(contours.size());
	for (int i = 0; i < contours.size(); ++i)
	cv::convexHull(cv::Mat(contours[i]), hull[i]);

	for (int i = 0; i < hull.size(); ++i)
	cv::drawContours(frame, hull, i, cv::Scalar(255.0F, 0.0F, 0.0F));
	*/
}