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

    // Continue
    DWORD baseAddress = GetProcessBaseAddress(processID);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);
    DWORD localPlayerAddress, entityList;


    // Read the value stored in baseAddress + 0x17E0A8 and store it in localPlayer
    // This is a pointer to the player's base address
    ReadProcessMemory(handle, LPCVOID(baseAddress + LOCAL_PLAYER_OFFSET), &localPlayerAddress, sizeof(localPlayerAddress), nullptr);
    ReadProcessMemory(handle, LPCVOID(baseAddress + ENTITY_LIST_OFFSET), &entityList, sizeof(entityList), nullptr);


    std::cout << "Handle ID: " << std::hex << processID << '\n';
    std::cout << "Base address: " << std::hex << baseAddress << '\n';
    std::cout << "Player Base Address: " << localPlayerAddress << "\n\n";

    // Create local player
    Entity localPlayer = Entity(localPlayerAddress, handle);

    // Create entity list
    std::vector<Entity> list;
    std::unordered_map<DWORD, bool> visitedAddresses;

    int k = 0;
    int totalPlayers;
    ReadProcessMemory(handle, LPCVOID(baseAddress + TOTAL_PLAYERS), &totalPlayers, sizeof(totalPlayers), nullptr);

    do
    {
        // Get pointer to entity
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        DWORD currentEntityAddress;
        ReadProcessMemory(handle, LPCVOID(entityList + 0x4 + 4*k), &currentEntityAddress, sizeof(currentEntityAddress), nullptr);


        // Use a hashmap to mark the address as visited


        // Make entity object and add to list if it has not already been visited (aka not added)
        if (!visitedAddresses[currentEntityAddress])
        {
            Entity currentEntity = Entity(currentEntityAddress, handle);
            {
                list.push_back(currentEntity);

                // Print entity info
                std::cout << k + 1 << ".\n";
                list[k].printInfo();
                std::cout << '\n';
                visitedAddresses[currentEntityAddress] = true;
            }

        }

        k++;
    } while (k < totalPlayers - 1);

    //Main hackloop
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        setHealth(handle, localPlayerAddress, 9999);

    }
    return 0;
}

