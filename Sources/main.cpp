#include "PalmReader.hpp"
#include "SettingsManager.hpp"

//=================================================================================================

int main(int argc, char** argv)
{
	pr::PalmReader(pr::SettingsManager(argv[0])).run();
	return 0;
}