#include "PalmReader.hpp"

//=================================================================================================

pr::PalmReader::PalmReader(const SettingsManager& settings) :
	settings(settings),
	capture(CV_CAP_ANY),
	detector(settings.palmSize),
	subtractor(settings.historyLength, settings.thresholdRate),
	running(false),
	learned(false),
	pause(settings.suspended)
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

	print("PalmReader is running!");
	showHelp();
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
	if (!isRunning())
		return;
	
	running = false;
	print("PalmReader stopped!");
}

//=================================================================================================

bool pr::PalmReader::isRunning() const
{
	return running;
}

//=================================================================================================

void pr::PalmReader::processFrame(cv::Mat& frame, cv::Mat& processedFrame) const
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
			print("Subtractor learned!");
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
	int key = ::tolower(cv::waitKey(settings.waitingTime));
	switch (key)
	{
	case VK_ESCAPE:
	case 'q':
		stop();
		break;
	case VK_SPACE:
	case 'p':
		switchPause();
		break;
	case 'h':
		showHelp();
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
	{
		learned = false;
		print("Recognition suspended!");
	}
	else
		print("Recognition resumed!");
}

//=================================================================================================

void pr::PalmReader::print(const std::string& message) const
{
	std::cout << "[System]: " << message << std::endl;
}

//=================================================================================================

void pr::PalmReader::showHelp() const
{
	std::cout
		<< "[Helper]:\n"
		<< "The PalmReader welcomes you!\n"
		<< "- Press 'Space' or 'P' to resume / suspend recognition.\n"
		<< "- Press 'H' to show this help.\n"
		<< "- Press 'Esc' or 'Q' to quit program.\n"
		<< "Writen by MatrixDeity, 2016 - 2017."
		<< std::endl;
}