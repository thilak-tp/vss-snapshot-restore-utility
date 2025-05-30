// Implementation of the Config class for managing configuration settings
#include "config.h"

Config::Config() {
	sourcePath = "";
	targetPath = "";
	blockSize = 1024 * 1024;
	noOfThreads = 1;
	noOfRetries = 0;
}

void Config::setSourcePath(std::string src) {
	sourcePath = src;
}

void Config::setTargetPath(std::string dst) {
	targetPath = dst;
}

void Config::setBlockSize(int bSize) {
	blockSize = bSize * 1024;
}

void Config::setNoOfThreads(int nThreads) {
	noOfThreads = nThreads;
}

void Config::setNoOfRetries(int nRetries) {
	noOfRetries = nRetries;
}


// A function to display the current configuration settings for debugging purposes
void Config::displayConfig(){

	std::cout << "Source Path: " << sourcePath << std::endl;
	std::cout << "Target Path: " << targetPath << std::endl;
	std::cout << "Block Size: " << blockSize << " bytes" << std::endl;
	std::cout << "Number of Threads: " << noOfThreads << std::endl;
	std::cout << "Number of Retries: " << noOfRetries << std::endl;
}