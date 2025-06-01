// Implementation of the VSSRestorer class for restoring files from a VSS snapshot.
#include "vss_restorer.h"


// A function to restore a single file from srcPath to dstPath.
bool VSSRestorer::restoreSingleFile(const std::wstring& srcPath, const std::wstring& dstPath) {
    // Opem the shadowcopy path
    HANDLE hSrc = CreateFileW(srcPath.c_str(), GENERIC_READ, FILE_SHARE_READ,
        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (hSrc == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to open source file: " << srcPath << std::endl;
        return false;
    }

    // Open the target path
    HANDLE hDst = CreateFileW(dstPath.c_str(), GENERIC_WRITE, 0, nullptr,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (hDst == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to create destination file: " << dstPath << std::endl;
        CloseHandle(hSrc);
        return false;
    }

    FILETIME ftCreate = {}, ftAccess = {}, ftWrite = {};

    // Read file timestamps
    if (!GetFileTime(hSrc, &ftCreate, &ftAccess, &ftWrite)) {
        std::wcerr << L"Warning: Failed to get timestamps from: " << srcPath << std::endl;
    }
    // Read file attributes
    DWORD fileAttrs = GetFileAttributesW(srcPath.c_str());
    if (fileAttrs == INVALID_FILE_ATTRIBUTES) {
        std::wcerr << L"Warning: Failed to get attributes from: " << srcPath << std::endl;
        fileAttrs = FILE_ATTRIBUTE_NORMAL;
    }


    const DWORD BUFFER_SIZE = getBlockSize();
    BYTE* buffer = new BYTE[BUFFER_SIZE];
    DWORD bytesRead = 0, bytesWritten = 0;

    // Read the source file path and write to the target file path
    while (ReadFile(hSrc, buffer, BUFFER_SIZE, &bytesRead, nullptr) && bytesRead > 0) {
        if (!WriteFile(hDst, buffer, bytesRead, &bytesWritten, nullptr)) {
            std::wcerr << L"Failed to write to destination file: " << dstPath << std::endl;
            delete[] buffer;
            CloseHandle(hSrc);
            CloseHandle(hDst);
            return false;
        }
    }
    
    delete[] buffer;
    CloseHandle(hSrc);
    // Apply timestamps to destination
    if (!SetFileTime(hDst, &ftCreate, &ftAccess, &ftWrite)) {
        std::wcerr << L"Warning: Failed to set timestamps for: " << dstPath << std::endl;
    }
    CloseHandle(hDst);
    // Set original file attributes 
    if (!SetFileAttributesW(dstPath.c_str(), fileAttrs)) {
        std::wcerr << L"Warning: Failed to set file attributes for: " << dstPath << std::endl;
    }

	std::cout << " < Done > " << std::endl;
    return true;
}

//A recursive function to restore the VSS snapshot from srcDir to dstDir.
bool VSSRestorer::restoreVSSSnapshot(const std::wstring& srcDir, const std::wstring& dstDir) {
   
    CreateDirectoryW(dstDir.c_str(), nullptr);
  

    std::wcout << "< Current Path being copied: " << dstDir << " > ";
    
    WIN32_FIND_DATAW findData;
    std::wstring searchPath = srcDir + L"\\*";
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
        return false;

    do {
        std::wstring item = findData.cFileName;
        if (item == L"." || item == L"..") continue;
        // Skip the "System Volume Information" folder
        if (item == L"System Volume Information") {
            continue;
        }
		// Skip the Recycle Bin folder
        if (item == L"$RECYCLE.BIN") {
            continue;
        }
        std::wstring srcPath = srcDir + L"\\" + item;
        std::wstring dstPath = dstDir + L"\\" + item;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // Recursive copy for subdirectories
            if (!restoreVSSSnapshot(srcPath, dstPath)) {
                std::wcerr << L"Failed to copy directory: " << srcPath << std::endl;
                FindClose(hFind);
                return false;
            }
        }
        else {
            // Copy file
            if (!restoreSingleFile(srcPath, dstPath)) {
                std::wcerr << L"Failed to copy file: " << srcPath << std::endl;
                FindClose(hFind);
                return false;
            }
        }
    } while (FindNextFileW(hFind, &findData));

    FindClose(hFind);
    return true;
}
 
// Returns true if the path (file or directory) exists.
bool VSSRestorer::pathExists(const std::wstring& path) {
    DWORD attributes = GetFileAttributesW(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES);
}
// Returns true if the given shadow copy path is accessible.
bool VSSRestorer::isShadowCopyAccessible(const std::wstring& path) {
    HANDLE h = CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        std::wcerr << L"Failed to open path: " << path << L" (Error " << err << L")\n";
        return false;
    }

    CloseHandle(h);
    return true;
}

// A function to check information given by the user
RetVal VSSRestorer::validateConfig(VSSRestorer* vssRestorer) {
	std::wstring src = vssRestorer->getSourcePath();
	std::wstring dst = vssRestorer->getTargetPath();
   
   
   // Validations for source VSS path
   if (src.find(L"\\\\?\\") != 0) {
	   std::cout << "Error! ShadowPath must be a UNC path starting with \\\\?\\" << std::endl;
	   return FAILED;
   }
   // Check if the shadow copy path is accessible
   if (!isShadowCopyAccessible(src)) {
       std::wcout << "Error! Shadow Snapshot Path is not accessible " << src << std::endl;
	   return FAILED;
   }

   // Validations for destination path
   if (!pathExists(dst)) {
       std::wcout << "Error! Target Path does not exist " << dst << std::endl;
       return FAILED;
   }

   // Blocksize validation
   if (vssRestorer->getBlockSize() <= 0) {
       std::cout << "Error! Blocksize cannot be 0 or negative" << std::endl;
       return FAILED;
   }
   /*
   // Number of threads validation
   if (vssRestorer->getNoOfThreads() <= 0) {
	   std::cout << "Error! Number of threads cannot be 0 or negative" << std::endl;
       return FAILED;
   }

   // Number of retries validation
   if (vssRestorer->getNoOfRetries() < 0) {
       std::cout << "Error! Number of retries cannot be negative" << std::endl;
       return FAILED;
   }
   */
   return SUCCESS;
}
