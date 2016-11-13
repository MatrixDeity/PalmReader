#include "PalmReader.hpp"

//=================================================================================================

int main()
{
	cv::Ptr<PalmReader> palmReader(new PalmReader);
	palmReader->run();
	return 0;
}