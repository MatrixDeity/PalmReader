#include "PalmReader.hpp"

//=================================================================================================

pr::PalmReader::PalmReader(const SettingsManager& settings) :
	WINDOW_NAME(settings.windowName),
	WAITING_TIME(settings.waitingTime),
	capture(CV_CAP_ANY),
	detector(settings),
	lastGesture(pr::Detector::Gesture::NONE),
	executor(),
	running(false),
	pause(settings.suspended)
{
	createCommands();
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
			subtractBackground(processedFrame);
			buildContours(frame, processedFrame);
			processGesture();
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

void pr::PalmReader::createCommands()
{
	executor.addCommand("showSystemInfo", []()
	{
		WinExec("msinfo32", SW_HIDE);
	});

	executor.addCommand("closeActiveWindow", []()
	{
		CloseWindow(GetActiveWindow());
	});
}

//=================================================================================================

void pr::PalmReader::processFrame(cv::Mat& frame, cv::Mat& processedFrame) const
{
	cv::flip(frame, frame, 1);
	cv::cvtColor(frame, processedFrame, cv::COLOR_RGBA2GRAY);
}

//=================================================================================================

void pr::PalmReader::subtractBackground(cv::Mat& processedFrame)
{
	if (!detector.isLearned())
	{
		detector.learnSubtractor(processedFrame);
		if (detector.isLearned())
			print("Detector is learned!");
	}
	else
		detector.applySubtractor(processedFrame);
}

//=================================================================================================

void pr::PalmReader::buildContours(cv::Mat& frame, const cv::Mat& processedFrame)
{
	if (!detector.isLearned())
		return;
	
	detector.buildContours(frame, processedFrame);
}

//=================================================================================================

void pr::PalmReader::processGesture()
{
	using Gesture = pr::Detector::Gesture;
	Gesture currentGesture = detector.recognize();
	if (lastGesture == currentGesture)
		return;
	switch (currentGesture)
	{
	case Gesture::FIRST:
		print("First gesture recognized!");
		executor.execute("showSystemInfo");
		break;
	case Gesture::SECOND:
		print("Second gesture recognized!");
		executor.execute("closeActiveWindow");
		break;
	default:
		return;
	}
	lastGesture = currentGesture;
}

//=================================================================================================

void pr::PalmReader::displayFrame(const cv::Mat& frame) const
{
	cv::imshow(WINDOW_NAME, frame);
}

//=================================================================================================

void pr::PalmReader::handleInput()
{
	int key = ::tolower(cv::waitKey(WAITING_TIME));
	switch (key)
	{
	case VK_SPACE:
	case 'p':
		switchPause();
		break;
	case 'c':
		showCommandsList();
		break;
	case 'h':
		showHelp();
		break;
	case VK_ESCAPE:
	case 'q':
		stop();
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
		detector.reset();
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

void pr::PalmReader::showCommandsList() const
{
	const pr::CommandExecutor::Commands& commands = executor.getCommands();
	print("Commands list: ");
	for (const auto& command : commands)
		std::cout << command.first << std::endl;
}

//=================================================================================================

void pr::PalmReader::showHelp() const
{
	std::cout
		<< "[Helper]: "
		<< "The PalmReader welcomes you!\n"
		<< "- Press 'Space' or 'P' to resume / suspend recognition.\n"
		<< "- Press 'C' to show commands list.\n"
		<< "- Press 'H' to show this help.\n"
		<< "- Press 'Esc' or 'Q' to quit program.\n"
		<< "Writen by MatrixDeity, 2017."
		<< std::endl;
}