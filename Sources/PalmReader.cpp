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
		detectPalm(frame);
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
	cv::equalizeHist(frame, frame);
}

//=================================================================================================

void PalmReader::displayFrame(const cv::Mat& frame) const
{
	cv::imshow(WINDOW_NAME, frame);
}

//=================================================================================================

void PalmReader::detectPalm(cv::Mat& frame)
{
	std::vector<cv::Rect> hands;
	classifier.detectMultiScale(frame, hands);
	if (!hands.empty())
		cv::rectangle(frame, hands[0], cv::Scalar(255, 0, 255));
}