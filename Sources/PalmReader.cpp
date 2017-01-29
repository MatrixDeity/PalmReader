#include "PalmReader.hpp"

//=================================================================================================

PalmReader::PalmReader() :
	capture(CV_CAP_ANY),
	classifier("Assets/hand.xml"),
	isRunning(false)
{
	cv::namedWindow(WINDOW_NAME);
}

//=================================================================================================

PalmReader::~PalmReader()
{
	cv::destroyAllWindows();
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
		displayFrame(frame);
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

//=================================================================================================

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

void PalmReader::processFrame(cv::Mat& frame) const
{
	cv::flip(frame, frame, 1);
	cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
}

//=================================================================================================

void PalmReader::displayFrame(const cv::Mat& frame) const
{
	cv::imshow(WINDOW_NAME, frame);
}