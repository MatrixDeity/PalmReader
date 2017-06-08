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
		Detector(int palmMinSize);
		~Detector();
		void drawContours(cv::Mat& frame, const cv::Mat& processedFrame);

	private:
		typedef std::vector<std::vector<cv::Point>> ContoursArray;

		ContoursArray contours;
		ContoursArray hull;
		std::vector<cv::Vec4i> hierarchy;
		int palmMinSize;

		ContoursArray::const_iterator findMaxArea();
	};
}

