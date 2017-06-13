#include "Detector.hpp"

//=================================================================================================

pr::Detector::Detector(const SettingsManager& settings) :
	PALM_MIN_SIZE(settings.palmMinSize),
	DEFECT_MIN_LENGTH(settings.defectMinLength),
	LEARNING_RATE(settings.learningRate),
	LEARNING_FRAMES(settings.learningFrames),
	subtractor(settings.historyLength, settings.thresholdRate),
	contours(),
	hull(1),
	hullNum(),
	defects(),
	hierarchy(),
	frameOfLearning(0)
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
		cv::convexHull(*workingContour, hull[0]);
		cv::convexHull(*workingContour, hullNum);
		cv::drawContours(frame, hull, 0, cv::Scalar(255.0, 0.0, 0.0));
		cv::convexityDefects(*workingContour, hullNum, defects);
	}
	else if (!defects.empty())
		defects.clear();
}

//=================================================================================================

pr::Detector::Gesture pr::Detector::recognize()
{
	int defNum = countValidDefects();
	if (defNum >= 5)
		return Gesture::SECOND;
	if (defNum == 2)
		return Gesture::FIRST;
	return Gesture::NONE;
}

//=================================================================================================

void pr::Detector::applySubtractor(cv::Mat& processedFrame)
{
	subtractor(processedFrame, processedFrame, 0.0);
}

//=================================================================================================

void pr::Detector::learnSubtractor(cv::Mat& processedFrame)
{
	subtractor(processedFrame, processedFrame, LEARNING_RATE);
	++frameOfLearning;
}

//=================================================================================================

bool pr::Detector::isLearned() const
{
	return frameOfLearning == LEARNING_FRAMES;
}

//=================================================================================================

void pr::Detector::reset()
{
	frameOfLearning = 0;
	contours.clear();
	hull[0].clear();
	hullNum.clear();
	defects.clear();
	hierarchy.clear();
}

//=================================================================================================

pr::Detector::ContoursArray::const_iterator pr::Detector::findMaxArea() const
{
	double maxSize(0.0), size;
	auto maxContour = contours.cend();
	for (auto itr = contours.cbegin(); itr != contours.cend(); ++itr)
	{
		size = cv::contourArea(*itr);
		if (size > maxSize && size >= PALM_MIN_SIZE)
		{
			size = maxSize;
			maxContour = itr;
		}
	}
	return maxContour;
}

//=================================================================================================

int pr::Detector::countValidDefects() const
{
	int counter = 0;
	for (const auto& defect : defects)
		if (static_cast<double>(defect(3)) / 256.0 >= DEFECT_MIN_LENGTH)
			++counter;
	return counter;
}