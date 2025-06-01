// -------------------------------------------------------------------------------------------------------------------------------
// Program: Volume Shadow Copy Restore Utility
// Description: This utility restores files from a Volume Shadow Copy snapshot to a specified target partition.
// -------------------------------------------------------------------------------------------------------------------------------

// Implicitly present headerfiles
#include <windows.h>
#include <iostream>
#include <string>



// Explicitly included headerfiles
#include "app_defs.h"
#include "config.h"
#include "vss_restorer.h"
#include "benchmark.h"

// Function to print the usage message
inline void printMessage() {
	//std::cout << "Usage: vssrestore.exe <shadow_volume_path> <target_partition_path>\nOptional Parameters:\n  -b        Specify the block size <KB>   (By default: 1024 kilobytes (1MB))\n  -t        Specify the number of threads (By default: 1)\n  -r        Retry Count                   (By default: 0)\n  --bench   To measure copy time          (in Milliseconds)\n  --debug   To display inputs being used" << std::endl;
	std::cout << "Usage: vssrestore.exe <shadow_volume_path> <target_partition_path>\nOptional Parameters:\n  -b        Specify the block size <KB>   (By default: 1024 kilobytes (1MB))\n  --bench   To measure copy time          (in Milliseconds)\n  --debug   To display inputs being used" << std::endl;
}

// Main function starts here
int wmain(int argc, wchar_t* argv[]) {


	
	// Check if the correct number of arguments is provided
	if (argc < 3) {
		printMessage();
		return FAILED;
	}
	
	// Initialize configuration object
	VSSRestorer vssRestorer;

	// Parse shadow volume path and target partition path that are mandatory arguements
	vssRestorer.setSourcePath(argv[1]);
	vssRestorer.setTargetPath(argv[2]);
	
	// Parse rest of the optional command line arguments
	for (int i = 3; i < argc; i++) {

		std::wstring arg = argv[i];

		if (arg == L"-b") {
			if (i + 1 >= argc) {
				std::wcout << "Missing value for " << arg << std::endl;
				return FAILED;
			}
			vssRestorer.setBlockSize(std::stoi(argv[++i]));
		}
		/*else if (arg == L"-t") {
			if (i + 1 >= argc) {
				std::wcout << "Missing value for " << arg << std::endl;
				return FAILED;
			}
			vssRestorer.setNoOfThreads(std::stoi(argv[++i]));
		}
		else if (arg == L"-r") {
			if (i + 1 >= argc) {
				std::wcout << "Missing value for " << arg << std::endl;
				return FAILED;
			}
			vssRestorer.setNoOfRetries(std::stoi(argv[++i]));
		}*/
		else if (arg == L"--bench") {
			vssRestorer.setToBenchmark(true);
		}

		else if (arg == L"--debug") {
			vssRestorer.setDebugFlag(true);
		}
		
		else {
			std::wcout << "Unknown argument: " << arg << std::endl;
			return FAILED;
		}
	}
	
	// Display the configuration if debug flag is set
	if(vssRestorer.getDebugFlag())
		vssRestorer.displayConfig();

	// Validate the input and configuration settings
	RetVal  retVal =  vssRestorer.validateConfig(&vssRestorer);
	if (retVal != SUCCESS) {
		std::cout << "<< Error! Input and configuration settings >>" << std::endl;
		return FAILED;
	}

	// If the benchmark flag is set, start the latency benchmark along with VSS snapshot restoration
	if (vssRestorer.getBenchmarkFlag()) {
		LatencyBenchmark bench;
		bench.start(); // Start the benchmark timer
		bool ret = vssRestorer.restoreVSSSnapshot(vssRestorer.getSourcePath(), vssRestorer.getTargetPath());
		bench.stop(); // Stop the benchmark timer
		if (!ret) {
			std::cout << "Error! The VSS Snapshot Restore Failed." << std::endl;
			return FAILED;
		}
		else {
			std::cout << "The VSS Snapshot restoration was successful!"<< std::endl;
		}
		bench.report(); // Display the benchmark results
		bench.reset();  // Reset the counter
	}
	else {
		// If the benchmark flag is not set, start VSS snapshot restoration without measuring time
		bool ret = vssRestorer.restoreVSSSnapshot(vssRestorer.getSourcePath(), vssRestorer.getTargetPath());
		if(!ret) {
			std::cout << "Error! The VSS Snapshot Restore Failed." << std::endl;
			return FAILED;
		}
		else {
			std::cout << "The VSS Snapshot restoration was successful!" << std::endl;
		}
	}
    
	return SUCCESS;
}