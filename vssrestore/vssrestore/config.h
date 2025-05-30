#pragma once
#include<string>
#include <iostream>
// Prototype of the Config class for managing configuration settings

class Config {
	std::string sourcePath;
	std::string targetPath;
	int blockSize;;
	int noOfThreads;
	int noOfRetries;

public:
	// Default constructor to initialize default values
	Config();
	
	// Setter functions to retrieve configuration values
	void setSourcePath(std::string src);
	void setTargetPath(std::string dst);
	void setBlockSize(int bSize);
	void setNoOfThreads(int nThreads);
	void setNoOfRetries(int nRetries);

	// Getter functions to access configuration values
	std::string getSourcePath() const;
	std::string getTargetPath() const;
	int getBlockSize() const;
	int getNoOfThreads() const;
	int getNoOfRetries() const;

	// A function to validate the configuration settings
	bool validateConfigValues(Config* config);

	// A function to display the current configuration settings for debugging purposes
	void displayConfig();

};
