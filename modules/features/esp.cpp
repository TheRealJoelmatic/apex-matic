#include <windows.h>
#include "../../offsets.h"
#include "../../memory/driver.h"
#include "../loop.h"
#include "../modules.h"
#include "bones.h"
#include "ultils.h"
#include "../../overlay/renderer.h"

void esp() {
	//
	//		This whole Function was for a test
	//		I need a full redo with skelltons ect
	//
	if (!modules::esp) {
		return;
	}

	//for wts
	uint64_t viewRenderer = Read<uint64_t>(base_address + OFF_VIEWRENDER);
	uint64_t MatrixPtr = Read<uint64_t>(viewRenderer + OFF_VIEWMATRIX);
	GameViewMatrix = Read<ViewMatrix>(MatrixPtr);

	for (int i = 0; i < 100; i++)
	{
		uintptr_t Entity = GetEntityById(i, base_address);
		if (Entity == 0)
			continue;

		DWORD64 EntityHandle = Read<DWORD64>(Entity + OFF_NAME);

		std::string Identifier = Read<std::string>(EntityHandle);
		LPCSTR IdentifierC = Identifier.c_str();

		if (strcmp(IdentifierC, "player")) {
			if (modules::espIgnoreSelf && Entity == localPlayer) {
				continue;
			}

			Vector3D localPlayerPos = Read<Vector3D>(localPlayer + OFF_LOCAL_ORIGIN);
			Vector3D playerFeetPos = Read<Vector3D>(Entity + OFF_LOCAL_ORIGIN);

			float distanceToEm = localPlayerPos.Distance(playerFeetPos);

			if (modules::espMaxDistance < distanceToEm) {
				continue;
			}

			Vector3D playerHeadPos = GetBonePositionByHitBox(Entity, HitboxType::Head);

			Vector2D screenPlayerFeetPos;
			if (!WorldToScreen(playerFeetPos, GameViewMatrix, screenPlayerFeetPos)) {
				continue;
			}

			Vector2D screenPlayerHeadPos;
			if (!WorldToScreen(playerHeadPos, GameViewMatrix, screenPlayerHeadPos)) {
				continue;
			}

			if (modules::snaplines) {
				renderer::drawLine({ screenSize.x / 2, 0 }, { screenPlayerFeetPos.x, screenPlayerFeetPos.y }, IM_COL32(255, 255, 255, 255), true);
			}

			if (modules::Boxs2d) {
				Vector3D L_Arm_ENDPos = GetBonePositionByHitBox(Entity, HitboxType::Lefthand);
				Vector3D R_Arm_ENDPos = GetBonePositionByHitBox(Entity, HitboxType::Righthand);

				Vector2D screenL_Arm_ENDPos;
				if (!WorldToScreen(L_Arm_ENDPos, GameViewMatrix, screenL_Arm_ENDPos)) {
					continue;
				}

				Vector2D screenR_Arm_ENDPos;
				if (!WorldToScreen(R_Arm_ENDPos, GameViewMatrix, screenR_Arm_ENDPos)) {
					continue;
				}

				float width = ((screenL_Arm_ENDPos.x - screenR_Arm_ENDPos.x) + ((screenPlayerFeetPos.y - screenPlayerHeadPos.y) / 1.20)) / 2; 
				renderer::drawBoxWithShadow({ screenPlayerHeadPos.x - width, screenPlayerHeadPos.y }, { screenPlayerFeetPos.x + width, screenPlayerFeetPos.y }, IM_COL32(255, 255, 255, 255), true);
			}

			if (modules::boneESP) {
				ImU32 skeletonColor = IM_COL32(255, 255, 255, 255);
				bool shadow = false;

				//midle
				Vector3D PelvisPos = GetBonePositionByHitBox(Entity, HitboxType::Hip);
				Vector3D ALitterHigherPelilesPos = GetBonePositionByHitBox(Entity, HitboxType::Stomach);
				Vector3D ChestPos = GetBonePositionByHitBox(Entity, HitboxType::LowerChest);
				Vector3D ALitterHigherChestPos = GetBonePositionByHitBox(Entity, HitboxType::UpperChest);
				Vector3D NeckPos = GetBonePositionByHitBox(Entity, HitboxType::Neck);
				Vector3D HeadPos = GetBonePositionByHitBox(Entity, HitboxType::Head);

				// Right arm
				Vector3D R_Arm_MiddleJointPos = GetBonePositionByHitBox(Entity, HitboxType::Rightshoulder);
				Vector3D R_Arm_MiddlePos = GetBonePositionByHitBox(Entity, HitboxType::RightelbowBone);
				Vector3D R_Arm_ENDPos = GetBonePositionByHitBox(Entity, HitboxType::Righthand);

				// Left arm
				Vector3D L_Arm_MiddleJointPos = GetBonePositionByHitBox(Entity, HitboxType::Leftshoulder);
				Vector3D L_Arm_MiddlePos = GetBonePositionByHitBox(Entity, HitboxType::Leftelbow);
				Vector3D L_Arm_ENDPos = GetBonePositionByHitBox(Entity, HitboxType::Lefthand);

				// Right leg
				Vector3D R_Leg_TopLegPos = GetBonePositionByHitBox(Entity, HitboxType::LeftThighs);
				Vector3D R_Leg_MiddlePos = GetBonePositionByHitBox(Entity, HitboxType::Leftknees);
				Vector3D R_Leg_BottemPos = GetBonePositionByHitBox(Entity, HitboxType::Leftleg);

				// Left leg
				Vector3D L_Leg_TopLegPos = GetBonePositionByHitBox(Entity, HitboxType::RightThighs);
				Vector3D L_Leg_MiddlePos = GetBonePositionByHitBox(Entity, HitboxType::Rightknees);
				Vector3D L_Leg_BottemPos = GetBonePositionByHitBox(Entity, HitboxType::Rightleg);

				// Middle
				Vector2D screenPelvisPos;
				if (!WorldToScreen(PelvisPos, GameViewMatrix, screenPelvisPos)) {
					continue;
				}

				Vector2D screenALitterHigherPelilesPos;
				if (!WorldToScreen(ALitterHigherPelilesPos, GameViewMatrix, screenALitterHigherPelilesPos)) {
					continue;
				}

				Vector2D screenChestPos;
				if (!WorldToScreen(ChestPos, GameViewMatrix, screenChestPos)) {
					continue;
				}

				Vector2D screenALitterHigherChestPos;
				if (!WorldToScreen(ALitterHigherChestPos, GameViewMatrix, screenALitterHigherChestPos)) {
					continue;
				}

				Vector2D screenNeckPos;
				if (!WorldToScreen(NeckPos, GameViewMatrix, screenNeckPos)) {
					continue;
				}

				Vector2D screenHeadPos;
				if (!WorldToScreen(HeadPos, GameViewMatrix, screenHeadPos)) {
					continue;
				}

				// Right arm
				Vector2D screenR_Arm_MiddleJointPos;
				if (!WorldToScreen(R_Arm_MiddleJointPos, GameViewMatrix, screenR_Arm_MiddleJointPos)) {
					continue;
				}

				Vector2D screenR_Arm_MiddlePos;
				if (!WorldToScreen(R_Arm_MiddlePos, GameViewMatrix, screenR_Arm_MiddlePos)) {
					continue;
				}

				Vector2D screenR_Arm_ENDPos;
				if (!WorldToScreen(R_Arm_ENDPos, GameViewMatrix, screenR_Arm_ENDPos)) {
					continue;
				}

				// Left arm
				Vector2D screenL_Arm_MiddleJointPos;
				if (!WorldToScreen(L_Arm_MiddleJointPos, GameViewMatrix, screenL_Arm_MiddleJointPos)) {
					continue;
				}

				Vector2D screenL_Arm_MiddlePos;
				if (!WorldToScreen(L_Arm_MiddlePos, GameViewMatrix, screenL_Arm_MiddlePos)) {
					continue;
				}

				// Right leg
				Vector2D screenR_Leg_TopLegPos;
				if (!WorldToScreen(R_Leg_TopLegPos, GameViewMatrix, screenR_Leg_TopLegPos)) {
					continue;
				}

				Vector2D screenR_Leg_MiddlePos;
				if (!WorldToScreen(R_Leg_MiddlePos, GameViewMatrix, screenR_Leg_MiddlePos)) {
					continue;
				}

				Vector2D screenR_Leg_BottemPos;
				if (!WorldToScreen(R_Leg_BottemPos, GameViewMatrix, screenR_Leg_BottemPos)) {
					continue;
				}

				// Left leg
				Vector2D screenL_Leg_TopLegPos;
				if (!WorldToScreen(L_Leg_TopLegPos, GameViewMatrix, screenL_Leg_TopLegPos)) {
					continue;
				}

				Vector2D screenL_Leg_MiddlePos;
				if (!WorldToScreen(L_Leg_MiddlePos, GameViewMatrix, screenL_Leg_MiddlePos)) {
					continue;
				}

				Vector2D screenL_Leg_BottemPos;
				if (!WorldToScreen(L_Leg_BottemPos, GameViewMatrix, screenL_Leg_BottemPos)) {
					continue;
				}

				Vector2D screenL_Arm_ENDPos;
				if (!WorldToScreen(L_Arm_ENDPos, GameViewMatrix, screenL_Arm_ENDPos)) {
					continue;
				}


				// Middle body
				renderer::drawLine(ImVec2(screenPelvisPos.x, screenPelvisPos.y), ImVec2(screenALitterHigherPelilesPos.x, screenALitterHigherPelilesPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenALitterHigherPelilesPos.x, screenALitterHigherPelilesPos.y), ImVec2(screenChestPos.x, screenChestPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenChestPos.x, screenChestPos.y), ImVec2(screenALitterHigherChestPos.x, screenALitterHigherChestPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenALitterHigherChestPos.x, screenALitterHigherChestPos.y), ImVec2(screenNeckPos.x, screenNeckPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenNeckPos.x, screenNeckPos.y), ImVec2(screenHeadPos.x, screenHeadPos.y), skeletonColor, shadow);

				// Right arm
				renderer::drawLine(ImVec2(screenNeckPos.x, screenNeckPos.y), ImVec2(screenR_Arm_MiddleJointPos.x, screenR_Arm_MiddleJointPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenR_Arm_MiddleJointPos.x, screenR_Arm_MiddleJointPos.y), ImVec2(screenR_Arm_MiddlePos.x, screenR_Arm_MiddlePos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenR_Arm_MiddlePos.x, screenR_Arm_MiddlePos.y), ImVec2(screenR_Arm_ENDPos.x, screenR_Arm_ENDPos.y), skeletonColor, shadow);

				// Left arm
				renderer::drawLine(ImVec2(screenNeckPos.x, screenNeckPos.y), ImVec2(screenL_Arm_MiddleJointPos.x, screenL_Arm_MiddleJointPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenL_Arm_MiddleJointPos.x, screenL_Arm_MiddleJointPos.y), ImVec2(screenL_Arm_MiddlePos.x, screenL_Arm_MiddlePos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenL_Arm_MiddlePos.x, screenL_Arm_MiddlePos.y), ImVec2(screenL_Arm_ENDPos.x, screenL_Arm_ENDPos.y), skeletonColor, shadow);

				// Right leg
				renderer::drawLine(ImVec2(screenPelvisPos.x, screenPelvisPos.y), ImVec2(screenR_Leg_TopLegPos.x, screenR_Leg_TopLegPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenR_Leg_TopLegPos.x, screenR_Leg_TopLegPos.y), ImVec2(screenR_Leg_MiddlePos.x, screenR_Leg_MiddlePos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenR_Leg_MiddlePos.x, screenR_Leg_MiddlePos.y), ImVec2(screenR_Leg_BottemPos.x, screenR_Leg_BottemPos.y), skeletonColor, shadow);

				// Left leg
				renderer::drawLine(ImVec2(screenPelvisPos.x, screenPelvisPos.y), ImVec2(screenL_Leg_TopLegPos.x, screenL_Leg_TopLegPos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenL_Leg_TopLegPos.x, screenL_Leg_TopLegPos.y), ImVec2(screenL_Leg_MiddlePos.x, screenL_Leg_MiddlePos.y), skeletonColor, shadow);
				renderer::drawLine(ImVec2(screenL_Leg_MiddlePos.x, screenL_Leg_MiddlePos.y), ImVec2(screenL_Leg_BottemPos.x, screenL_Leg_BottemPos.y), skeletonColor, shadow);
			}
		}
	}
}