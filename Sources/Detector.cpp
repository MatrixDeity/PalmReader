#include "Detector.hpp"

//=================================================================================================

pr::Detector::Detector(double palmMinSize) :
	contours(),
	hierarchy(),
	hull(1),
	hullNum(),
	defects(),
	palmMinSize(palmMinSize)
{
}

//=================================================================================================

pr::Detector::~Detector()
{
}

//=================================================================================================

void pr::Detector::buildContours(cv::Mat& frame, const cv::Mat& processedFrame)
{
	findContours(processedFrame, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE,
		cv::Point(0, 0));
	auto workingContour = findMaxArea();
	if (workingContour != contours.end())
	{
		cv::convexHull(*workingContour, hull[0], false, true);
		cv::convexHull(*workingContour, hullNum, false, false);
		cv::drawContours(frame, hull, 0, cv::Scalar(255.0, 0.0, 0.0));
		cv::convexityDefects(*workingContour, hullNum, defects);
	}
	else if (defects.size() != 0)
		defects.resize(0);
}

//=================================================================================================

pr::Detector::Gesture pr::Detector::recognize()
{
	switch (defects.size())
	{
	case 3:
		return Gesture::FIRST;
		break;
	case 6:
		return Gesture::SECOND;
		break;
	case 0:
	case 1:
	default:
		return Gesture::NONE;
		break;
	}
}

//=================================================================================================

pr::Detector::ContoursArray::const_iterator pr::Detector::findMaxArea() const
{
	double maxSize(0.0), size;
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