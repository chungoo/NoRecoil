// NoRecoil.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "windows.h"
#include <iostream>
#include <string>
#include <signal.h>

//with different weapons, there are different fire rate and recoil.
DWORD recoilStep;
DWORD fireRate;


bool LeftMouseDown = true;
int leftMouseVKCode = 1;
int RecoilState = 4;       //default state is turned off;

						   //to be changed into real game window name
LPCTSTR windowsName = L"UnrealWindow";

void __stdcall RemoveRecoil()
{
	HWND foregroundWin;

	leftMouseVKCode = 1;
	while (1)
	{
		foregroundWin = GetForegroundWindow();
		if (foregroundWin == FindWindow(windowsName, 0) && RecoilState == 3)
		{
			if (LeftMouseDown)
			{
				Sleep(fireRate);
				mouse_event(1u, 0, recoilStep, 0, 3u);
			}
		}
		Sleep(1u);
	}
}

void __stdcall KeyHandlerThread()
{
	while (1)
	{
		if (GetAsyncKeyState(0x78) < 0)           // F9 turns recoil reducer on.
		{
			RecoilState = 3;
			Beep(0x320u, 0xC8u);
		}
		if (GetAsyncKeyState(0x79) < 0)           // F10 turns recoil reducer off.
		{
			RecoilState = 4;
			Beep(0x64u, 0xC8u);
		}
		LeftMouseDown = GetAsyncKeyState(leftMouseVKCode) < 0;
		Sleep(1u);
	}
}

bool bQuit = false;
void quit(int a) {
	bQuit = true;
}

int main() {

	std::cout << "please select favorite weapon: [1-7]\n";
	std::cout << "1. AKM\n";
	std::cout << "2. SCAR-L\n";
	std::cout << "3. M16A4\n";
	std::cout << "4. M416\n";
	std::cout << "5. UMP9\n";
	std::cout << "6. SKS\n";
	std::cout << "7. UZI\n";
	/*
	id   weapon   fireRate   recoilUp
	-----------------------------
	 1    AKM      0.100s     8
	 2    SCAR-L   0.096s     7
	 3    M16A4    0.075s     7
	 4    M416     0.086s     7
	 5    UMP9     0.092s     5
	 6    SKS      0.090s     8
	 7    UZI      0.048s     5
	*/
	char choice;
	std::cin.get(choice);
	std::string sWeaponName;
	switch (choice) {
	case '1':
		recoilStep = 8u;
		fireRate = 100u;
		sWeaponName = "AKM";
		break;
	case '2':
		recoilStep = 7u;
		fireRate = 96u;
		sWeaponName = "SCAR-L";
		break;
	case '3':
		recoilStep = 7u;
		fireRate = 75u;
		sWeaponName = "M16A4";
		break;
	case '4':
		recoilStep = 7u;
		fireRate = 86u;
		sWeaponName = "M416";
		break;
	case '5':
		recoilStep = 5u;
		fireRate = 92u;
		sWeaponName = "UMP9";
		break;
	case '6':
		recoilStep = 8u;
		fireRate = 90u;
		sWeaponName = "SKS";
		break;
	case '7':
		recoilStep = 5u;
		fireRate = 48u;
		sWeaponName = "UZI";
		break;
	default:
		std::cout << "Please the input a number between 1 to 7.\n";
		return -1;
	}

	std::cout << "Selected weapon: " << sWeaponName << std::endl;
	std::cout << "press 'F9' to enable, 'F10' to disable, 'Ctrl+C' to quit\n";
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RemoveRecoil, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyHandlerThread, 0, 0, 0);

	signal(SIGINT, quit);
	while (!bQuit) { Sleep(1000u); }
}