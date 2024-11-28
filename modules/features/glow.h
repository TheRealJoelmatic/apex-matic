#pragma once
#ifndef GLOW_H
#define GLOW_H

#include <windows.h>
#include "../../offsets.h"
#include "../../memory/driver.h"
#include "../loop.h"
#include "../modules.h"

inline bool isVisible(uintptr_t entity) {

	float WorldTime = Read<float>(entity + OFF_TIME_BASE);
	if (WorldTime == 0) {
		WorldTime = 200;
	}
	//std::cout << WorldTime << std::endl;
	float Time1 = Read<float>(entity + OFF_LAST_VISIBLE_TIME);
	return (Time1 + 0.2) >= WorldTime;
}

inline void EnableHighlight(DWORD64 Entity, int glowMode) {


	write<bool>(Entity + OFF_GLOW_ENABLE, true);
	write<int>(Entity + OFF_GLOW_HIGHLIGHT_ID, glowMode);
	write<int>(Entity + OFF_GLOW_FIX, 0);

	//std::cout << Entity << std::endl;
}

inline void ViewModelGlow(DWORD64 Entity, int glowMode) {
	if (modules::ViewModelGlows) {
		// Weapon Glow
		uint64_t actWeaponID = Read<uint64_t>(Entity + OFF_VIEWMODELS) & 0xFFFF;
		uint64_t currentWeapon = Read<uint64_t>(base_address + OFF_ENTITY_LIST + (actWeaponID << 5));

		write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID, glowMode);
	}
}

inline void glowThread() {
	while (true)
	{
		try {
			Sleep(10);

			if (!IsValidPointer(localPlayer)) {
				continue;
			}

			ViewModelGlow(localPlayer, modules::ViewModelglowMode);


			if (Entitys.empty()) {
				continue;
			}

			for (DWORD64 Entity : Entitys) {

				bool islocalPlayer = localPlayer == Entity;
				if (!(modules::glowIgnoreSelf && islocalPlayer)) {
					if (modules::glow) {
						if (modules::staticGlow) {
							EnableHighlight(Entity, modules::glowMode);
						}
						else {
							int glowmode = 20; //full white

							if (islocalPlayer) {
								glowmode = 20; //green
								EnableHighlight(Entity, glowmode);
							}
							else {
								bool IsVisible = isVisible(Entity);

								if (IsVisible) {
									glowmode = 19; //green
								}
								else {
									Vector3D PlayerLocation = Read<Vector3D>(localPlayer + OFF_LOCAL_ORIGIN);
									Vector3D EntityLocation = Read<Vector3D>(Entity + OFF_LOCAL_ORIGIN);

									float Distance = PlayerLocation.Distance(EntityLocation);
									//std::cout << "distance: " << Distance << std::endl;
									if (Distance > 1200) {
										glowmode = 59;
									}
									else {
										glowmode = 1;
									}
								}
								EnableHighlight(Entity, glowmode);
							}
						}
					}
				}
			}
		}
		catch (const std::exception& e) {
			
		}
	}
}

#endif // GLOW_H