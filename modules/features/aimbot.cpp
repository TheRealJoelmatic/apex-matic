#include <windows.h>
#include <vector>
#include "../../math/Vector3D.hpp"
#include "../loop.h"
#include "../../memory/driver.h"
#include "../../offsets.h"
#include "../../math/Matrix.hpp"
#include "../../math/FloatVector3D.hpp"

#include "aimbot.h"
#include "../../math/QAngle.hpp"
#include "../../math/Resolver.hpp"
#include "../modules.h"
#include "ultils.h"
#include "../../utils/HitboxType.hpp"
#include "bones.h"
#include "../../global.h"


//
//		Aimbot need some work it works but 
//		close up its a bit shit
//		Note: Add prediction 
//


//
// player
//
float distance(const Vector2D& v1, const Vector2D& v2) {
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return std::sqrt(dx * dx + dy * dy);
}

bool IsWithinFOV(const Vector2D& screenPosition, const Vector2D& screenCenter, float radius) {
	float distanceFromCenter = std::hypot(screenPosition.x - screenCenter.x, screenPosition.y - screenCenter.y);
	return distanceFromCenter <= radius;
}

Vector3D FindBestTarget(const std::vector<DWORD64>& entities) {
	if (entities.empty()) {
		return { 0, 0, 0 };
	}

	Vector3D playerPosition = Read<Vector3D>(localPlayer + OFF_LOCAL_ORIGIN);
	float closestDistance = 99999999999;
	Vector3D closestTargetPosition = { 0, 0, 0 };
	float fovRadius = modules::AimFOV * 100;
	Vector2D screenCenter = { screenSize.x / 2, screenSize.y / 2 };

	for (const auto& entity : entities) {
		if (modules::aimbotIngoreKnocked) {
			bool IsKnocked = Read<short>(entity + OFF_BLEEDOUT_STATE) > 0;
			if (IsKnocked) continue;
		}

		Vector3D targetPosition = GetBonePositionByHitBox(entity, HitboxType::Neck);

		// Skip invalid positions
		if (targetPosition.x == 0 && targetPosition.y == 0 && targetPosition.z == 0) {
			continue;
		}

		float distanceFromPlayer = playerPosition.Distance(targetPosition);
		if (distanceFromPlayer > modules::aimbotMaxDistance) {
			continue;
		}

		Vector2D screenPosition;
		if (!WorldToScreen(targetPosition, GameViewMatrix, screenPosition)) {
			continue;
		}

		if (!IsWithinFOV(screenPosition, screenCenter, fovRadius)) {
			continue;
		}

		float num = screenCenter.x - screenPosition.x;
		float num2 = screenCenter.y - screenPosition.y;
		float distanceToCenter = sqrtf(num * num + num2 * num2);

		// Combine distance from player and distance to screen center
		float combinedDistance =
			((distanceFromPlayer / 100) * 0.75)
			+
			(distanceToCenter / 100);

		if (combinedDistance < closestDistance) {
			closestDistance = combinedDistance;
			closestTargetPosition = targetPosition;
		}
	}

	return closestTargetPosition;
}

bool GetAngleToTarget(Vector3D Target, QAngle& Angle) {
	Angle = Resolver::CalculateAngle(CameraPosition, Target);
	return true;
}

float lerp(float start, float end, float t) {
	return start + t * (end - start);
}

inline Vector2D NormalizeVectorAngles(Vector2D angle) {
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f) {
		angle.y += 360.f;
	}

	return angle;
}

//
// aimbot
//

void aimbot(std::vector<DWORD64> Entitys) {
	if (!modules::aimbot) {
		return;
	}

	if (!(GetAsyncKeyState(VK_RBUTTON) & 0x8000)) {
		return;
	}

	if (Entitys.size() <= 0)
		return;

	Vector3D TargetPos = FindBestTarget(Entitys);
	if ((TargetPos.x == 0 && TargetPos.y == 0 && TargetPos.z == 0)) {
		std::cout << "No target found! " << std::endl;
		return;
	}

	Vector2D ScreenPosition;
	WorldToScreen(TargetPos, GameViewMatrix, ScreenPosition);
	std::cout << "X: " << ScreenPosition.x << " Y: " << ScreenPosition.y << std::endl;

	QAngle DesiredAngles = QAngle(0, 0);
	if (!GetAngleToTarget(TargetPos, DesiredAngles)) {
		std::cout << "1. Angle Failed" << std::endl;
		return;
	}
	if (DesiredAngles == QAngle(0, 0)) {
		std::cout << "2. Angle Failed" << std::endl;
		return;
	}

	Vector2D currentAngle = Read<Vector2D>(localPlayer + OFF_VIEW_ANGLES);
	QAngle CurrentQAngle(currentAngle.x, currentAngle.y);

	// Calculate the difference in angles
	QAngle angleDifference = DesiredAngles - CurrentQAngle;

	// Apply speed factor (0 is fastest, larger values are slower)
	QAngle smoothedAngles = CurrentQAngle + angleDifference * (1.0f / (modules::speed + 1));

	if (IsValidPointer(localPlayer + OFF_VIEW_ANGLES)) {
		write<Vector2D>(localPlayer + OFF_VIEW_ANGLES, NormalizeVectorAngles(Vector2D(smoothedAngles.x, smoothedAngles.y)));
	}
}

void aimbotThread() {
	while (true)
	{
		Sleep(10);

		if (Entitys.empty()) {
			continue;
		}

		aimbot(Entitys);
	}
}