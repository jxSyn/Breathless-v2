//
//  antiaim.hpp
//  vHook
//
#pragma once

#include "main.h"

extern Vector atTargets;

enum VIEW_ANTIAIM_PITCH
{
    Emotion     = 1,
    Dance       = 2,
    FakeDown    = 3,
    FakeUp      = 4,
};

enum VIEW_ANTIAIM_YAW
{
    Backwards   = 1,
    LowerYaw    = 2,
    manedgee    = 3,
    LBYbreak    = 4,
};

enum VIEW_ANTIIAIM_FYAW
{
    Rand = 1,
    Rand2 = 2,
    Rand3 = 3,
    lower135 = 4,
    oneeighro = 5,
    
};

enum VIEW_ANTIIAIM_MYAW
{
    LowerBody       = 1,
    BackJitter      = 2,
    Rotate          = 3,
};

enum VIEW_ANTIIAIM_AYAW
{
    LowerBod        = 1,
    Rotatee         = 2,
};

void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon);
void antiResolverFlip(CUserCmd* cmd, C_BaseEntity* local);
void manualAAIndicators();
//void GetBestHeadAngle(CUserCmd* cmd, C_BasePlayer* local);
//void DoOffsets(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket);













