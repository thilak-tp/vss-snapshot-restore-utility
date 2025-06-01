#pragma once
// Declaration of a configuration class used to hold input paths and application configurations

// Implicit headerfiles
#include<string>
#include <iostream>

// Explicit headerfiles
#include "app_defs.h"

class Config {
	std::wstring sourcePath;
	std::wstring targetPath;
	int blockSize;;
	//int noOfThreads;
	//int noOfRetries;
	bool benchmarkFlag;
	bool debugFlag;

public:
	// Default constructor to initialize default values
	Config();
	
	// Setter functions to retrieve configuration values
	void setSourcePath( std::wstring  src);
	void setTargetPath( std::wstring  dst);
	void setBlockSize(float bSize);
	//void setNoOfThreads(int nThreads);
	//void setNoOfRetries(int nRetries);
	void setToBenchmark(bool benchmark);
	void setDebugFlag(bool debug);

	// Getter functions to access configuration values
	const std::wstring  getSourcePath() const;
	const std::wstring  getTargetPath() const;
	float getBlockSize() const;
	//int getNoOfThreads() const;
	//int getNoOfRetries() const;
	bool getBenchmarkFlag() const;
	bool getDebugFlag() const;

	// A function to display the current configuration settings for debugging purposes
	void displayConfig();

};
