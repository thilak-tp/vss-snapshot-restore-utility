// Implementation of the Config class for managing configuration settings
#include "config.h"
#include "app_defs.h"


Config::Config() {
	sourcePath = "";
	targetPath = "";
	blockSize = 1024 * 1024;
	noOfThreads = 1;
	noOfRetries = 0;
}
// Setters for the configuration settings implementation
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

// Getters for the configuration settings implementation
std::string Config::getSourcePath() const {
	return sourcePath;
}

std::string Config::getTargetPath() const {
	return targetPath;
}

int Config::getBlockSize() const {
	return blockSize;
}

int Config::getNoOfThreads() const {
	return noOfThreads;
}

int Config::getNoOfRetries() const {
	return noOfRetries;
}

// A function to validate the configuration settings
bool Config::validateConfigValues(Config* config) {
	if (config->getBlockSize() <= 0) {
		std::cout << "Invalid Blocksize! Block size cannot be negative or zero" << std::endl;
		return FAILED;
	}
	if (config->getNoOfThreads() <= 0) {
		std::cout << "Invalid Number of Threads! Must be greater than 0" << std::endl;
		return FAILED;
	}
	if(config->getNoOfRetries() < 0) {
		std::cout << "Invalid Number of Retries! Retries count cannot be negative" << std::endl;
		return FAILED;
	}

	return SUCCESS;
}

// A function to display the current configuration settings for debugging purposes
void Config::displayConfig(){

	std::cout << "Source Path: " << sourcePath << std::endl;
	std::cout << "Target Path: " << targetPath << std::endl;
	std::cout << "Block Size: " << blockSize << " bytes" << std::endl;
	std::cout << "Number of Threads: " << noOfThreads << std::endl;
	std::cout << "Number of Retries: " << noOfRetries << std::endl;
}