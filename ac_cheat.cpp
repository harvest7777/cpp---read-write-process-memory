#include "includes.h"
int main()
{
    const wchar_t* acClient = L"ac_client.exe";
    DWORD processID = GetProcessID(acClient);

    if (!processID)
    {
        std::cout << "Couldn't find handle ID\n";
        return 0;
    }

    DWORD baseAddress = GetProcessBaseAddress(processID);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);

    std::cout << "Handle ID: " << std::hex << processID << '\n';
    std::cout << "Base address: " << std::hex << baseAddress << '\n';

    DWORD localPlayerBaseAddress;

    int playerHealth;
    int newHealth = 9999;
    
    // Read the value stored in baseAddress + 0x17E0A8 and store it in localPlayer
    // This is a pointer to the player's base address
    ReadProcessMemory(handle, LPCVOID(baseAddress + 0x17E0A8), &localPlayerBaseAddress, sizeof(localPlayerBaseAddress), nullptr);

    // 0xEC is the offset from player to health
    // Unlike localPlayerBaseAddress, playerHealth is NOT a pointer
    // The pointer to the player's health is localPlayerBaseAddress + 0xEC
    // playerHealth is a local variable stored in main which simply stores the player's health
    ReadProcessMemory(handle, LPCVOID(localPlayerBaseAddress + 0xEC), &playerHealth, sizeof(playerHealth), nullptr);

    std::cout << "Player Base Address: " << localPlayerBaseAddress << '\n';
    std::cout << "Player Health: " << std::dec << playerHealth << '\n';

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        WriteProcessMemory(handle, LPVOID(localPlayerBaseAddress + 0xEC), &newHealth, sizeof(newHealth), nullptr);
    }

}

