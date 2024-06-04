#pragma once
#include "Windows.h"
#include "offsets.h"
#include <iostream>
#include "structs.h"
#include "includes.h"
void setHealth(HANDLE handle, DWORD localPlayerAddress, int newHealth);
coordinates getPlayerPosition(HANDLE handle, DWORD localPlayerAddress);
void teleportToCoordinates(HANDLE handle, DWORD localPlayerAddress, coordinates pos);
std::string getEntityName(HANDLE handle, DWORD entityAddress);
int getEntityHp(HANDLE handle, DWORD entityAddress);
bool isValidEntity(Entity e);