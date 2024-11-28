#include <iostream>

#include "loop.h"
#include "../offsets.h"
#include "../ext/xor/xor_cc.hpp"
#include "../memory/driver.h"
#include "../global.h"
#include "../memory/utils.h"
#include <TlHelp32.h>
#include "features/glow.h"
#include "features/aimbot.h"
#include "../math/Matrix.hpp"
#include "features/skin.h"
#include "modules.h"
#include <thread>
#include "../overlay/overlay.h"
#include "../overlay/renderer.h"
#include "features/esp.h"
#include "../ext/spoofer/CallStack-Spoofer.h"

int get_process_id(std::wstring process_name) {
	SPOOF_FUNC;

	PROCESSENTRY32W processentry;
	HandlePtr snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(PROCESSENTRY32W);

	while (Process32NextW(snapshot_handle.get(), &processentry) == TRUE) {
		std::wstring exe_file(processentry.szExeFile);
		if (process_name.compare(exe_file) == 0) {
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}

//
//
//	MAIN CHEAT STUFF
//
//
DWORD64 GetEntityById(int Ent, DWORD64 Base)
{
	SPOOF_FUNC;
	DWORD64 EntityList = Base + OFF_ENTITY_LIST;
	DWORD64 BaseEntity = Read<DWORD64>(EntityList);
	if (!BaseEntity)
		return NULL;

	return  Read<DWORD64>(EntityList + (Ent << 5));
}


int cheatloop()
{
	SPOOF_FUNC;
	system("cls");

	std::cout << _("[+] Made by @Joelmatic [+]") << std::endl;


	if (!find_driver())
	{
		std::cout << _("[ :( ] Failed to find driver's handle.") << std::endl;
		system("pause");
		return -1;
	}


	std::cout << _("[!] Waiting for apex") << std::endl;

	process_id = 0;
	base_address = 0;
	while (process_id == 0) {
		process_id = get_process_id(L"r5apex.exe");
		Sleep(1000);
	}
	std::cout << _("[+] Found Apex") << std::endl;

	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);
	if (screenSize.y == 0 || screenSize.x == 0) {
		system("cls");
		std::cout << _("[ :( ] Faild to get screen size") << std::endl;
		system("pause");
		return -1;
	}

	std::cout << _("[+] PID: ") << process_id << std::endl;
	while (base_address == 0) {
		//r5apex.exe
		base_address = find_image();
		image_base = base_address;
		Sleep(1000);
	}
	std::cout << _("[+] Base Address: ") << base_address << std::endl;

	dtbs = resolve_dtb();

	if (!dtbs)
	{
		std::cout << _("[ :( ] Failed to target process directory table base.") << std::endl;
		system("cls");
		return -1;
	}

	std::cout << _("[+] Got target directory table base: 0x%llx", dtbs);

	std::cout << _("[+] LOADING PELASE WAIT") << std::endl;

	//Note: make aimbot a thread
	std::thread T_glowThread(glowThread);

	Sleep(1500);
	Beep(500, 500);

	//system("cls");
	std::cout << _("[+] LOADED") << std::endl;

	while (1)
	{
		try {
			//for player
			localPlayer = Read<DWORD64>(base_address + OFF_LOCAL_PLAYER);
			CameraPosition = Read<Vector3D>(localPlayer + OFF_CAMERAORIGIN);

			//for wts
			uint64_t viewRenderer = Read<uint64_t>(base_address + OFF_VIEWRENDER);
			uint64_t MatrixPtr = Read<uint64_t>(viewRenderer + OFF_VIEWMATRIX);
			GameViewMatrix = Read<ViewMatrix>(MatrixPtr);

			skinChanger(localPlayer);

			Entitys.clear();
			for (int i = 0; i < 100; i++)
			{
				uintptr_t Entity = GetEntityById(i, base_address);
				if (Entity == 0)
					continue;

				DWORD64 EntityHandle = Read<DWORD64>(Entity + OFF_NAME);

				std::string Identifier = Read<std::string>(EntityHandle);
				LPCSTR IdentifierC = Identifier.c_str();

				if (strcmp(IdentifierC, "player")) {
					Entitys.push_back(Entity);
				}
			}

			aimbot(Entitys);
		}
		catch (const std::exception& e) {

		}

	}
}