#include "Detector.hpp"

//=================================================================================================

pr::Detector::Detector(int palmMinSize) :
	contours(),
	hierarchy(),
	hull(1),
	palmMinSize(palmMinSize)
{
}

//=================================================================================================

pr::Detector::~Detector()
{
}

//=================================================================================================

void pr::Detector::drawContours(cv::Mat& frame, const cv::Mat& processedFrame)
{
	findContours(processedFrame, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE,
		cv::Point(0, 0));
	auto maxArea = findMaxArea();
	if (maxArea != contours.end())
	{
		cv::convexHull(cv::Mat(*maxArea), hull[0]);
		cv::drawContours(frame, hull, 0, cv::Scalar(255.0F, 0.0F, 0.0F));
	}
}

//=================================================================================================

pr::Detector::ContoursArray::const_iterator pr::Detector::findMaxArea() const
{
	int maxSize(0), size;
	auto maxContour = contours.cend();
	for (auto itr = contours.cbegin(); itr != contours.cend(); ++itr)
	{
		size = cv::contourArea(*itr);
		if (size > maxSize && size >= palmMinSize)
		{
			size = maxSize;
			maxContour = itr;
		}
	}
	return maxContour;
}