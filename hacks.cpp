#include "hacks.h"
void setHealth(HANDLE handle, DWORD localPlayerAddress, int newHealth)
{
	WriteProcessMemory(handle, LPVOID(localPlayerAddress + HEALTH_OFFSET), &newHealth, sizeof(newHealth), nullptr);
}

coordinates getPlayerPosition(HANDLE handle, DWORD localPlayerAddress)
{
	float playerX, playerY, playerZ;
	ReadProcessMemory(handle, LPCVOID(localPlayerAddress + X_POS_OFFSET), &playerX, sizeof(playerX), nullptr);
	ReadProcessMemory(handle, LPCVOID(localPlayerAddress + Y_POS_OFFSET), &playerY, sizeof(playerY), nullptr);
	ReadProcessMemory(handle, LPCVOID(localPlayerAddress + Z_POS_OFFSET), &playerZ, sizeof(playerZ), nullptr);

	return { playerX, playerY, playerZ };
}

void teleportToCoordinates(HANDLE handle, DWORD localPlayerAddress, coordinates pos)
{
	WriteProcessMemory(handle, LPVOID(localPlayerAddress + X_POS_OFFSET), &pos.x, sizeof(pos.x), nullptr);
	WriteProcessMemory(handle, LPVOID(localPlayerAddress + Y_POS_OFFSET), &pos.y, sizeof(pos.y), nullptr);
	WriteProcessMemory(handle, LPVOID(localPlayerAddress + Z_POS_OFFSET), &pos.z, sizeof(pos.z), nullptr);
}

std::string getEntityName(HANDLE handle, DWORD entityAddress)
{
	//Gets entity's name and returns a string
	char currentChar;
	int byteOffset = 0;
	std::string name;
	int charsRead = 0;
	do
	{
		ReadProcessMemory(handle, LPCVOID(entityAddress + NAME_OFFSET + byteOffset), &currentChar, sizeof(currentChar), nullptr);
		name += currentChar;
		byteOffset++;
		charsRead++;
	} while (!(currentChar == '\0') && charsRead < 25);
	return name;
}

int getEntityHp(HANDLE handle, DWORD entityAddress)
{
	// Gets entity's hp and returns it in hex
	int entityHp;
	ReadProcessMemory(handle, LPCVOID(entityAddress + HEALTH_OFFSET), &entityHp, sizeof(entityHp), nullptr);
	return entityHp;
}

bool isValidEntity(Entity e)
{
	return (e.health >= 0 && e.health <= 100 && e.x > -800 && e.x < 800 && e.y > -800 && e.y < 800 && e.z > -800 && e.z < 800 && e.name.size() > 0 && e.name.size() < 25);
}