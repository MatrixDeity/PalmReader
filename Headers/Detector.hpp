#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "SettingsManager.hpp"

//=================================================================================================

namespace pr
{
	class Detector
	{
	public:
		enum class Gesture
		{
			NONE,
			FIRST,
			SECOND
		};

		Detector(const SettingsManager& settings);
		~Detector();
		void buildContours(cv::Mat& frame, const cv::Mat& processedFrame);
		void reset();
		Gesture recognize();
		void applySubtractor(cv::Mat& processedFrame);
		void learnSubtractor(cv::Mat& processedFrame);
		bool isLearned() const;

	private:
		typedef std::vector<std::vector<cv::Point>> ContoursArray;

		const double PALM_MIN_SIZE;
		const double DEFECT_MIN_LENGTH;
		const double LEARNING_RATE;
		const int LEARNING_FRAMES;

		cv::BackgroundSubtractorMOG2 subtractor;
		ContoursArray contours;
		ContoursArray hull;
		std::vector<int> hullNum;
		std::vector<cv::Vec4i> defects;
		std::vector<cv::Vec4i> hierarchy;
		int frameOfLearning;

		ContoursArray::const_iterator findMaxArea() const;
		int countValidDefects() const;
	};
}

