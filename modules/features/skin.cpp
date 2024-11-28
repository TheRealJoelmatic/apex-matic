#include "../modules.h"
#include "../../memory/driver.h"
#include "../../offsets.h"
#include <map>
#include "../../utils/Weapons.hpp"
#include "../../global.h"

void skinChanger(DWORD64 _localPlayer) {
    if (!modules::SkinChanger) {
        return;
    }

    DWORD64 LastWeapon = Read<DWORD64>(_localPlayer + OFF_WEAPON_HANDLE) & 0xFFFF; //m_latestPrimaryWeapons 
    DWORD64 Weapon = Read<DWORD64>(base_address + OFF_ENTITY_LIST + (LastWeapon << 5)); //cl_entitylist
    int WeaponSkin = Read<int>(Weapon + OFF_SKIN);
    if (modules::oneSize) {
        write<int>(Weapon + OFF_SKIN, modules::SkinId);
    }

    int _skinID = 0;
    int waponIndex = Read<int>(Weapon + OFF_WEAPON_INDEX);
    //std::cout << "Current Skin ID:" << waponIndex << std::endl;

    // LOL
    // Works but ik I could do better

    if (waponIndex == WeaponIDs::P2020) {
        _skinID = modules::SkinChangerValues::SkinP2020;
    }
    else if (waponIndex == WeaponIDs::RE45) {
        _skinID = modules::SkinChangerValues::SkinRE45;
    }
    else if (waponIndex == WeaponIDs::ALTERNATOR) {
        _skinID = modules::SkinChangerValues::SkinALTERNATOR;
    }
    else if (waponIndex == WeaponIDs::R99) {
        _skinID = modules::SkinChangerValues::SkinR99;
    }
    else if (waponIndex == WeaponIDs::R301) {
        _skinID = modules::SkinChangerValues::SkinR301;
    }
    else if (waponIndex == WeaponIDs::SPITFIRE) {
        _skinID = modules::SkinChangerValues::SkinSPITFIRE;
    }
    else if (waponIndex == WeaponIDs::G7) {
        _skinID = modules::SkinChangerValues::SkinG7;
    }

    else if (waponIndex == WeaponIDs::FLATLINE) {
        _skinID = modules::SkinChangerValues::SkinFLATLINE;
    }
    else if (waponIndex == WeaponIDs::HEMLOCK) {
        _skinID = modules::SkinChangerValues::SkinHEMLOCK;
    }
    else if (waponIndex == WeaponIDs::PROWLER) {
        _skinID = modules::SkinChangerValues::SkinPROWLER;
    }
    else if (waponIndex == WeaponIDs::REPEATER) {
        _skinID = modules::SkinChangerValues::SkinREPEATER;
    }
    else if (waponIndex == WeaponIDs::RAMPAGE) {
        _skinID = modules::SkinChangerValues::SkinRAMPAGE;
    }
    else if (waponIndex == WeaponIDs::CAR) {
        _skinID = modules::SkinChangerValues::SkinCAR;
    }

    else if (waponIndex == WeaponIDs::HAVOC) {
        _skinID = modules::SkinChangerValues::SkinHAVOC;
    }
    else if (waponIndex == WeaponIDs::LSTAR) {
        _skinID = modules::SkinChangerValues::SkinLSTAR;
    }
    else if (waponIndex == WeaponIDs::TRIPLETAKE) {
        _skinID = modules::SkinChangerValues::SkinTRIPLETAKE;
    }
    else if (waponIndex == WeaponIDs::VOLT) {
        _skinID = modules::SkinChangerValues::SkinVOLT;
    }
    else if (waponIndex == WeaponIDs::NEMESIS) {
        _skinID = modules::SkinChangerValues::SkinNEMESIS;
    }

    else if (waponIndex == WeaponIDs::MOZAMBIQUE) {
        _skinID = modules::SkinChangerValues::SkinMOZAMBIQUE;
    }
    else if (waponIndex == WeaponIDs::PEACEKEEPER) {
        _skinID = modules::SkinChangerValues::SkinPEACEKEEPER;
    }
    else if (waponIndex == WeaponIDs::MASTIFF) {
        _skinID = modules::SkinChangerValues::SkinMASTIFF;
    }

    else if (waponIndex == WeaponIDs::WINGMAN) {
        _skinID = modules::SkinChangerValues::SkinWINGMAN;
    }
    else if (waponIndex == WeaponIDs::LONGBOW) {
        _skinID = modules::SkinChangerValues::SkinLONGBOW;
    }
    else if (waponIndex == WeaponIDs::CHARGE_RIFLE) {
        _skinID = modules::SkinChangerValues::SkinCHARGE_RIFLE;
    }
    else if (waponIndex == WeaponIDs::SENTINEL) {
        _skinID = modules::SkinChangerValues::SkinSENTINEL;
    }

    else if (waponIndex == WeaponIDs::EVA8) {
        _skinID = modules::SkinChangerValues::SkinEVA8;
    }
    else if (waponIndex == WeaponIDs::DEVOTION) {
        _skinID = modules::SkinChangerValues::SkinDEVOTION;
    }
    else if (waponIndex == WeaponIDs::BOCEK) {
        _skinID = modules::SkinChangerValues::SkinBOCEK;
    }
    else if (waponIndex == WeaponIDs::KRABER) {
        _skinID = modules::SkinChangerValues::SkinKRABER;
    }

    if (_skinID == 0)
        return;

    write<int>(Weapon + OFF_SKIN, _skinID);
}


void hairloom() {
    //Off UC not working and will crash game
    /*
        uintptr_t ViewModelHandle = read<uintptr_t>(LocalEntity.Address+ OFFSET_VIEWMODEL) & 0xFFFF;
    uintptr_t ViewModel = read<uintptr_t>(oBaseAddress + OFFSET_LOCAL_ENT + (ViewModelHandle <<5));
    //write<int>(LocalEntity.WeaponEntity + OFFSET_SKIN, 65);
    write<int>(ViewModel + OFFSET_CURFRAME, 912);
    write<std::string>(ViewModel + OFFSET_MODELNAME, "mdl/weapons/kunai/ptpov_kunai_wraith.rmdl");
    */
}