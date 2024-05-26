#include "includes.h"
#include "hacks.h"
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
    DWORD localPlayerAddress;

    std::cout << "Handle ID: " << std::hex << processID << '\n';
    std::cout << "Base address: " << std::hex << baseAddress << '\n';

    int newHealth = 9999;
    
    // Read the value stored in baseAddress + 0x17E0A8 and store it in localPlayer
    // This is a pointer to the player's base address
    ReadProcessMemory(handle, LPCVOID(baseAddress + LOCAL_PLAYER_OFFSET), &localPlayerAddress, sizeof(localPlayerAddress), nullptr);


    std::cout << "Player Base Address: " << localPlayerAddress << '\n';
    coordinates playerPos;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        setHealth(handle, localPlayerAddress, 9999);

        if (GetAsyncKeyState('Q') & 0x8000)
        {
            std::cout << "Waypoint saved at'";
            playerPos.printCoordinates();
            playerPos = getPlayerPosition(handle, localPlayerAddress);
        }
        
        if (GetAsyncKeyState('U') & 0x8000)
        {
            std::cout << "Teleporting to ";
            playerPos.printCoordinates();
            teleportToCoordinates(handle, localPlayerAddress, playerPos);
        }
    }

}

