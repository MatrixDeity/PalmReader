#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

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

		Detector(double palmMinSize, double defectMinLength);
		~Detector();
		void buildContours(cv::Mat& frame, const cv::Mat& processedFrame);
		void reset();
		Gesture recognize();

	private:
		typedef std::vector<std::vector<cv::Point>> ContoursArray;

		const double PALM_MIN_SIZE;
		const double DEFECT_MIN_LENGTH;

		ContoursArray contours;
		ContoursArray hull;
		std::vector<int> hullNum;
		std::vector<cv::Vec4i> defects;
		std::vector<cv::Vec4i> hierarchy;

		ContoursArray::const_iterator findMaxArea() const;
		int countValidDefects() const;
	};
}

