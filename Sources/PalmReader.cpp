#include "PalmReader.hpp"

//=================================================================================================

PalmReader::PalmReader() :
	capture(CV_CAP_ANY),
	detector(100),
	running(false)
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
	if (isRunning())
		return;
	running = true;

	cv::Mat frame, negative;
	int counter = 0;
	while (isRunning())
	{
		capture >> frame;
		processFrame(frame);
		prepareNegative(frame, negative); // Try to pass the same variable
		displayFrame(frame);
		handleInput();
	}
}

//=================================================================================================

void PalmReader::stop()
{
	if (isRunning())
		running = false;
}

//=================================================================================================

bool PalmReader::isRunning() const
{
	return running;
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

void PalmReader::processFrame(cv::Mat& frame)
{
	cv::flip(frame, frame, 1);
}

//=================================================================================================

void PalmReader::displayFrame(const cv::Mat& frame) const
{
	cv::imshow(WINDOW_NAME, frame);
}

//=================================================================================================

void PalmReader::prepareNegative(const cv::Mat& frame, cv::Mat& negative)
{
	static int callCounter = 0;

	negative = frame;
	detector.subtractBackground(negative);
	if (callCounter >= IDLE_FRAMES)
	{
		detector.drawContours(negative);
	}
	else
		++callCounter;
}