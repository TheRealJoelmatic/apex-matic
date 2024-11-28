#pragma once
namespace modules {

	inline bool menuopen = true;

	inline bool aimbot = false;
	inline bool aimbotIngoreKnocked = true;
	inline bool fovcirlce = true;
	inline bool fovincirlce = false;
	inline float AimFOV = 3.0f;
	inline float aimbotMaxDistance = 3000;
	inline float speed = 5;
	inline float smoothness = 10;

	inline bool esp = false;
	inline bool espIgnoreSelf = true;
	inline float espMaxDistance = 10000;
	inline bool boneESP = false;
	inline bool Boxs2d = false;
	inline bool snaplines = false;

	inline bool glow = false;

	inline int glowMode = 1;
	inline bool glowIgnoreSelf = false;
	inline bool staticGlow = false;

	inline bool ViewModelGlows = false;
	inline int ViewModelglowMode = 75;

	inline bool SkinChanger = false;
	inline bool oneSize = false;
	inline int SkinId = 2;
	inline int BoneId = 0;

	inline bool streamproof = true;

	inline bool crosshair = false;

	inline bool DisplayFPS = false;

	namespace SkinChangerValues {
		// Weapon IDs
		// Light
		inline int SkinP2020 = 1;
		inline int SkinRE45 = 1;
		inline int SkinALTERNATOR = 1;
		inline int SkinR99 = 1;
		inline int SkinR301 = 1;
		inline int SkinSPITFIRE = 1;
		inline int SkinG7 = 1;

		// Heavy
		inline int SkinFLATLINE = 1;
		inline int SkinHEMLOCK = 1;
		inline int SkinREPEATER = 1;
		inline int SkinRAMPAGE = 1;
		inline int SkinCAR = 1;

		// Energy
		inline int SkinHAVOC = 1;
		inline int SkinDEVOTION = 1;
		inline int SkinLSTAR = 1;
		inline int SkinTRIPLETAKE = 1;
		inline int SkinVOLT = 1;
		inline int SkinNEMESIS = 1;

		// Shotgun
		inline int SkinMOZAMBIQUE = 1;
		inline int SkinEVA8 = 1;
		inline int SkinPEACEKEEPER = 1;
		inline int SkinMASTIFF = 1;

		// Snipers
		inline int SkinLONGBOW = 1;
		inline int SkinCHARGE_RIFLE = 1;
		inline int SkinSENTINEL = 1;

		// Legendary
		inline int SkinWINGMAN = 1;
		inline int SkinPROWLER = 1;
		inline int SkinBOCEK = 1;
		inline int SkinKRABER = 1;
	}
}