#pragma once
// Declaration of VSSRestorer class for restoring files from VSS snapshots

// Implicit headerfiles
#include <string>
#include "config.h"
#include <windows.h>
#include <iostream>

// Explicit headerfiles
#include <algorithm>
#include "app_defs.h"
#include <vector>
#include <thread>
#include <future>

class VSSRestorer : public Config {

public:
	// A function to check if the target path exists
	bool pathExists(const std::wstring& path);
	// A function to check if the shadow copy path is accessible
	bool isShadowCopyAccessible(const std::wstring& path);
	// A function to check if the config values are valid
	RetVal validateConfig(VSSRestorer* vssRestorer);
	// A function to restore the shadow copy to a specific drive
	bool restoreSingleFile(const std::wstring& srcPath, const std::wstring& dstPath);
	// A function to restore single files
	bool restoreVSSSnapshot(const std::wstring& srcDir, const std::wstring& dstDir);

};
