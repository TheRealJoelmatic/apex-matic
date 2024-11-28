#pragma once
#include "../../math/Matrix.hpp"
#include "../../utils/HitboxType.hpp"
#include "../../global.h"


//
// Maths
//
inline bool WorldToScreen(Vector3D WorldPosition, ViewMatrix GameViewMatrix, Vector2D& ScreenPosition) {
	Vector3D transformed = GameViewMatrix.Transform(WorldPosition);

	if (transformed.z < 0.001) {
		return false;
	}

	transformed.x *= 1.0 / transformed.z;
	transformed.y *= 1.0 / transformed.z;

	ScreenPosition = Vector2D(screenSize.x / 2.0f + transformed.x * (screenSize.x / 2.0f), screenSize.y / 2.0f - transformed.y * (screenSize.y / 2.0f));

	return true;
}