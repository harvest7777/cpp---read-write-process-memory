#include "includes.h"
int main()
{
    const wchar_t* acClient = L"ac_client.exe";
    DWORD processID = GetProcessID(acClient);
    if (processID)
    {
        std::cout << "Found handle ID: " << processID << '\n';

    }
    else
    {
        std::cout << "Couldn't find handle ID\n";
    }
}

