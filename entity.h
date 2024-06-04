#pragma once
#include "includes.h"
class Entity
{
	private:
		DWORD baseAddress;
		HANDLE handle;
		void updateHp();
		void updateName();
		void updatePosition();
	public:
		Entity(DWORD baseAddr, HANDLE h);
		int health;
		std::string name;
		float x, y, z;
		void teleportToPosition(float newX, float newY, float newZ);
		void updateEntity();
		void printInfo();
};

