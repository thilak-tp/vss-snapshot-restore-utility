// Implementation of the Config class for managing configuration settings and for storing paths provided by the user.
#include "config.h"


Config::Config() {
	sourcePath = L"";
	targetPath = L"";
	blockSize = 1024 * 1024;
	noOfThreads = 1;
	noOfRetries = 0;
	benchmarkFlag = false;
	debugFlag = false;
}

// Setters for the configuration settings implementation
void Config::setSourcePath(std::wstring src) {
	sourcePath = src;
}
void Config::setTargetPath(std::wstring dst) {
	targetPath = dst;
}
void Config::setBlockSize(float bSize) {
	blockSize = bSize * 1024;
}
void Config::setNoOfThreads(int nThreads) {
	noOfThreads = nThreads;
}
void Config::setNoOfRetries(int nRetries) {
	noOfRetries = nRetries;
}
void Config::setToBenchmark(bool benchmark) {
	benchmarkFlag = benchmark;
}
void Config::setDebugFlag(bool debug) {
	debugFlag = debug;
}

// Getters for the configuration settings implementation
const std::wstring  Config::getSourcePath() const {
	return sourcePath;
}
const std::wstring  Config::getTargetPath() const {
	return targetPath;
}
float Config::getBlockSize() const {
	return blockSize;
}
int Config::getNoOfThreads() const {
	return noOfThreads;
}
int Config::getNoOfRetries() const {
	return noOfRetries;
}
bool Config::getBenchmarkFlag() const {
	return benchmarkFlag;
}
bool Config::getDebugFlag() const {
	return debugFlag;
}


// A function to display the current configuration settings for debugging purposes
void Config::displayConfig(){
	float blockSizeInMB = getBlockSize() / (1024 * 1024); // Convert to MB for display
	float blockSizeInKB = getBlockSize() / 1024; // Convert to KB for display
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	std::wcout <<"Source Path       : " << sourcePath << std::endl;
	std::wcout <<"Target Path       : " << targetPath << std::endl;
	std::cout << "Block Size        : " << blockSize << " bytes " << "| "<< blockSizeInKB << " KB" << " | " << blockSizeInMB << " MB |" <<std::endl;
	std::cout << "Number of Threads : " << noOfThreads << std::endl;
	std::cout << "Number of Retries : " << noOfRetries << std::endl;
	std::cout << "Benchmark Flag    : " << benchmarkFlag << std::endl;
	std::cout << "Debug Flag        : " << debugFlag << std::endl;
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}