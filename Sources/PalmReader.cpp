#include "PalmReader.hpp"

//=================================================================================================

PalmReader::PalmReader() :
capture(CV_CAP_ANY),
isRunning(false)
{
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
}

//=================================================================================================

PalmReader::~PalmReader()
{
	cv::destroyWindow(WINDOW_NAME);
}

//=================================================================================================

void PalmReader::run()
{
	if (isRunning)
		return;
	isRunning = true;

	cv::Mat frame;
	while (isRunning)
	{
		capture >> frame;
		processFrame(frame);
		cv::imshow(WINDOW_NAME, frame);
		handleInput();
	}
}

//=================================================================================================

void PalmReader::stop()
{
	if (isRunning)
		isRunning = false;
}

//=================================================================================================

bool PalmReader::getStatus() const
{
	return isRunning;
}

void PalmReader::handleInput()
{
	int key = cv::waitKey(WAITING_TIME);
	switch (key)
	{
	case VK_ESCAPE:
		stop();
		break;
	default:
		break;
	}
}

//=================================================================================================

void PalmReader::processFrame(cv::Mat& frame)
{
	cv::flip(frame, frame, 1);
}