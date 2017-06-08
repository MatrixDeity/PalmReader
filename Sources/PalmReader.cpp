#include "PalmReader.hpp"

//=================================================================================================

pr::PalmReader::PalmReader(SettingsManager& settings) :
	settings(settings),
	capture(CV_CAP_ANY),
	detector(settings.palmSize),
	subtractor(settings.historyLength, settings.thresholdRate),
	running(false),
	learned(false),
	pause(true)
{
	cv::namedWindow(settings.windowName);
}

//=================================================================================================

pr::PalmReader::~PalmReader()
{
	cv::destroyAllWindows();
}

//=================================================================================================

void pr::PalmReader::run()
{
	if (isRunning())
		return;
	running = true;

	cv::Mat frame, processedFrame;
	while (isRunning())
	{
		capture >> frame;
		processFrame(frame, processedFrame);
		if (!pause)
		{
			applySubtractor(processedFrame);
			buildContours(frame, processedFrame);
		}
		displayFrame(frame);
		handleInput();
	}
}

//=================================================================================================

void pr::PalmReader::stop()
{
	if (isRunning())
		running = false;
}

//=================================================================================================

bool pr::PalmReader::isRunning() const
{
	return running;
}

//=================================================================================================

void pr::PalmReader::processFrame(cv::Mat& frame, cv::Mat& processedFrame)
{
	cv::flip(frame, frame, 1);
	cv::cvtColor(frame, processedFrame, cv::COLOR_RGBA2GRAY);
}

//=================================================================================================

void pr::PalmReader::applySubtractor(cv::Mat& frame)
{
	static int callingCounter = 0;

	if (!learned)
	{
		subtractor(frame, frame, settings.learningRate);
		++callingCounter;
		if (callingCounter >= settings.idleFrames)
		{
			learned = true;
			callingCounter = 0;
		}
	}
	else
	{
		subtractor(frame, frame, 0.0);
	}
}

//=================================================================================================

void pr::PalmReader::buildContours(cv::Mat& frame, const cv::Mat& processedFrame)
{
	if (!learned)
		return;
	
	detector.drawContours(frame, processedFrame);
}

//=================================================================================================

void pr::PalmReader::displayFrame(const cv::Mat& frame) const
{
	cv::imshow(settings.windowName, frame);
}

//=================================================================================================

void pr::PalmReader::handleInput()
{
	int key = cv::waitKey(settings.waitingTime);
	switch (key)
	{
	case VK_ESCAPE:
		stop();
		break;
	case VK_RETURN:
		switchPause();
		break;
	default:
		break;
	}
}

//=================================================================================================

void pr::PalmReader::switchPause()
{
	pause = !pause;
	if (pause)
		learned = false;
}