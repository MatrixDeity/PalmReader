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

		Detector(double palmMinSize);
		~Detector();
		void buildContours(cv::Mat& frame, const cv::Mat& processedFrame);
		Gesture recognize();

	private:
		typedef std::vector<std::vector<cv::Point>> ContoursArray;

		ContoursArray contours;
		ContoursArray hull;
		std::vector<int> hullNum;
		std::vector<cv::Vec4i> defects;
		std::vector<cv::Vec4i> hierarchy;
		double palmMinSize;

		ContoursArray::const_iterator findMaxArea() const;
	};
}

