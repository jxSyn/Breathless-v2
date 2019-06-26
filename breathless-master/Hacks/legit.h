//
//  aimbot.hpp
//  vHook
//
#pragma once

#include "main.h"

void DoLegitAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide);



namespace LegitAim
{
    extern C_BaseEntity* curTarget;
}





