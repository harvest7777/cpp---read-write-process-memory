#pragma once
#include "Windows.h"
#include "offsets.h"
#include "structs.h"
void setHealth(HANDLE handle, DWORD localPlayerAddress, int newHealth);
coordinates getPlayerPosition(HANDLE handle, DWORD localPlayerAddress);
void teleportToCoordinates(HANDLE handle, DWORD localPlayerAddress, coordinates pos);