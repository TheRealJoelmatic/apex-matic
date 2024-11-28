#pragma once
#include <Windows.h>
#include "../math/Vector3D.hpp"
#include "../math/Matrix.hpp"
#include <vector>

inline Vector3D CameraPosition;
inline ViewMatrix GameViewMatrix;
inline uintptr_t localPlayer;
inline std::vector<uintptr_t> Entitys;

int cheatloop();
DWORD64 GetEntityById(int Ent, DWORD64 Base);