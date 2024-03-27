#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

class IO_DATA
{
public:
	static std::string chooseOpenFile(int nrFileName = 0);
	static std::string chooseSaveFile(int nrFileName = 0);
	static bool saveToFile(std::string fileName, const char *outputData, const size_t dataSize, bool appendData);
	static bool readFromFile(std::string fileName, std::vector<char>& inputData);
};

