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
		
		if (counter < IDLE_FRAMES)
		{
			prepareNegative(frame, negative); // Try to pass the same variable
		}
		else
			++counter;

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
	negative = frame;
	detector.subtractBackground(negative);
	detector.drawContour(negative);
}