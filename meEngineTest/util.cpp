#include <string>
#include <fstream>

#include "util.h"

int getFileSize(const std::string &fileName)
{
	std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!file.is_open())
	{
		return -1;
	}
	file.seekg(0, std::ios::end);
	int fileSize = (int)file.tellg();
	file.close();
	return fileSize;
}