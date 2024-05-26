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
