#include "getprocessid.h"

DWORD GetProcessID(const wchar_t* processName)
{
	// Initialize a process ID and handle snapshot (list of all current handles)
	DWORD processID{ 0 };
	HANDLE hSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };

	// Error catching
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to get handle";
		return processID;
	}

	// Make a processentry (contains info on current process)
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	// Pass in handles and pointer to the PROCESSENTRY32 struct
	// Process32First will write values of the current handle to the processEntry
	if (Process32First(hSnapshot, &processEntry))
	{
		do
		{
			// Compare the wchar* of process name and the processEntry's name (0 means same name)
			// It basically goes to the pointer, compares the first char, then the next and next and next until it reaches \0
			if (wcscmp(processEntry.szExeFile, processName) == 0)
			{
				processID = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &processEntry));

	}
	CloseHandle(hSnapshot);
	return processID;
}

DWORD GetProcessBaseAddress(DWORD processID) 
{
	DWORD processBaseAddress{ 0 };
	HANDLE hSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID) };
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to get handle";
		return processBaseAddress;
	}
	MODULEENTRY32 modEntry;
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &modEntry))
	{
		processBaseAddress = (DWORD)modEntry.modBaseAddr;
	}

	CloseHandle(hSnapshot);
	return processBaseAddress;

}