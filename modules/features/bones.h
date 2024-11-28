#pragma once
#include <Windows.h>
#include <cstdint>
#include "../../math/Vector2D.hpp"
#include "../../math/Vector3D.hpp"
#include "../../utils/HitboxType.hpp"
#include "../../memory/driver.h"
#include "../../offsets.h"
#include "../../math/Matrix.hpp"

inline Vector3D GetEntityBasePosition(uintptr_t pEntityBase)
{
	auto pos = Read<Vector3D>(pEntityBase + OFF_LOCAL_ORIGIN);
	return  pos;
}

inline Vector3D GetEntityBonePosition(uintptr_t pEntityBase, uint32_t dwBoneId)
{
	uintptr_t pBone = Read<uintptr_t>(pEntityBase + OFF_BONES);
	Matrix3x4 matBonePosition = Read<Matrix3x4>(pBone + (dwBoneId * 0x30));
	Vector3D vecBonePosition = { matBonePosition.matrix[0][3], matBonePosition.matrix[1][3], matBonePosition.matrix[2][3] };
	return GetEntityBasePosition(pEntityBase).Add(vecBonePosition);
}


inline Vector3D GetEntityBonePos(uintptr_t pEntityBase, uint32_t dwBoneId)
{
	uintptr_t pBone = Read<uintptr_t>(pEntityBase + OFF_BONES);

	Vector3D EntityHead = Vector3D();
	Vector3D BasePosition = GetEntityBasePosition(pEntityBase);
	EntityHead.x = Read<float>((pBone + 0xCC + (dwBoneId * 0x30))) + BasePosition.x;
	EntityHead.y = Read<float>((pBone + 0xDC + (dwBoneId * 0x30))) + BasePosition.y;
	EntityHead.z = Read<float>((pBone + 0xEC + (dwBoneId * 0x30))) + BasePosition.z;
	return EntityHead;
}

inline Vector3D GetBonePositionByHitBox(uintptr_t pEntityBase, HitboxType ID)
{
    Vector3D origin = Read<Vector3D>(pEntityBase + OFF_LOCAL_ORIGIN);
    //BoneByHitBox
    uint64_t Model = Read<uint64_t>(pEntityBase + OFF_STUDIOHDR);

    //get studio hdr
    uint64_t StudioHdr = Read<uint64_t>(Model + 0x8);

    //get hitbox array
    uint16_t HitboxCache = Read<uint16_t>(StudioHdr + 0x34);
    uint64_t HitBoxsArray = StudioHdr + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));

    uint16_t IndexCache = Read<uint16_t>(HitBoxsArray + 0x4);
    int HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));

    uint16_t Bone = Read<uint16_t>(HitBoxsArray + HitboxIndex + (static_cast<int>(ID) * 0x20));

    if (Bone < 0 || Bone > 255)
        return Vector3D();

    //hitpos
    uint64_t BoneArray = Read<uint64_t>(pEntityBase + OFF_BONES);
    uintptr_t Add = BoneArray + Bone * sizeof(Matrix3x4);
    Matrix3x4 Matrix = Read<Matrix3x4>(Add);

    return Vector3D(Matrix.matrix[0][3] + origin.x, Matrix.matrix[1][3] + origin.y, Matrix.matrix[2][3] + origin.z);
}