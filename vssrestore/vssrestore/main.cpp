
/* Read from a VSS snapshot effieciently and write it into a given partition
 Take shadow volume path, output partition path and the blocksize as command line arguements
 Pass the above arguments to a function that will read the VSS snapshot and write it efficiently to the output partition*/

// Implicitly present headerfiles
#include <windows.h>
#include <iostream>

// Explicitly included headerfiles
#include "app_defs.h"
#include "config.h"

int main(int argc, char *argv[]) {

	// Check if the correct number of arguments is provided
	if (argc < 3) {
		std::cout << "Usage: vssrestore.exe <shadow_volume_path> <target_partition_path>\nOptions:\n  -b        Specify the block size <KB> (By default: 1024 kilobytes (1MB))\n  -t        Specify the number of threads(By default: 1)\n  -r        Retry Count (By default 0)";
		return FAILED;
	}
	
	// Initialize configuration object
	Config config;
	
	// Parse first two command line arguments
	config.setSourcePath(argv[1]);
	config.setTargetPath(argv[2]);
	
	// Parse rest of the command line arguments
	for (int i = 3; i < argc; i++) {
		
		std::string arg = argv[i];
		
		if (arg == "-b") {
			if (i + 1 >= argc) {
				std::cout << "Missing value for " << arg << std::endl;
				return FAILED;
			}
			config.setBlockSize(std::stoi(argv[++i]));
		}
		else if (arg == "-t") {
			if (i + 1 >= argc) {
				std::cout << "Missing value for " << arg << std::endl;
				return FAILED;
			}
			config.setNoOfThreads(std::stoi(argv[++i]));
		}
		else if (arg == "-r") {
			if (i + 1 >= argc) {
				std::cout << "Missing value for " << arg << std::endl;
				return FAILED;
			}
			config.setNoOfRetries(std::stoi(argv[++i]));
		}
		else {
			std::cout << "Unknown argument: " << arg << std::endl;
			return FAILED;
		}	
	}


	config.displayConfig();
	return SUCCESS;
}