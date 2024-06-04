#include "entity.h"
Entity::Entity(DWORD baseAddr, HANDLE h)
{
	baseAddress = baseAddr;
	handle = h;
	updateHp();
	updateName();
	updatePosition();

}

void Entity::updateHp()
{
	//Read the entity's hp into hp attribute
	ReadProcessMemory(handle, LPCVOID(baseAddress + HEALTH_OFFSET), &health, sizeof(health), nullptr);

}
void Entity::updateName()
{
	char currentChar;
	int byteOffset = 0;
	std::string tempName;

	do
	{
		ReadProcessMemory(handle, LPCVOID(baseAddress + NAME_OFFSET + byteOffset), &currentChar, sizeof(currentChar), nullptr);
		tempName += currentChar;
		byteOffset++;
	} while (!(currentChar == '\0'));
	name = tempName;
}

void Entity::updatePosition()
{
	ReadProcessMemory(handle, LPCVOID(baseAddress + X_POS_OFFSET), &x, sizeof(x), nullptr);
	ReadProcessMemory(handle, LPCVOID(baseAddress + Y_POS_OFFSET), &y, sizeof(y), nullptr);
	ReadProcessMemory(handle, LPCVOID(baseAddress + Z_POS_OFFSET), &z, sizeof(z), nullptr);

}

void Entity::teleportToPosition(float newX, float newY, float newZ)
{
	WriteProcessMemory(handle, LPVOID(baseAddress + X_POS_OFFSET), &newX, sizeof(newX), nullptr);
	WriteProcessMemory(handle, LPVOID(baseAddress + Y_POS_OFFSET), &newY, sizeof(newY), nullptr);
	WriteProcessMemory(handle, LPVOID(baseAddress + Z_POS_OFFSET), &newZ, sizeof(newZ), nullptr);
}

void::Entity::updateEntity()
{
	updateHp();
	updateName();
	updatePosition();
}

void::Entity::printInfo()
{
	std::cout << "Name: " << name << '\n' << "HP:   " << std::dec << health << '\n' << "Pos:  (" << x << ", " << y << ", " << z << ")\n";
}