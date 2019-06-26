//
//  aimbot.cpp
//  vHook
//

#include "legit.h"
#include "autoshoot.h"
#include "antiaim.h"
#include "autowall.h"

C_BaseEntity* LegitAim::curTarget = nullptr; //here


//here
int MakeLegitHitscan(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            
            break;
            
    }
    
    if(vars.aimbot.legitHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}



void NormalizeAnglesLol(Vector& angle) {
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}

Vector Smooth(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.smooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    // if(activeWeapon->IsSnipScope() || activeWeapon->IsShotGun())
    //     vars.aimbot.smooth = false;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.smoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}





void DoLegitAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide)//here
{
    
    if(!vars.aimbot.LegitEnabled)
        return;
    
    Vector eyepos = local->GetEyePosition();
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        
        Vector vFrom, vTo;
        
        LegitAim::curTarget = entity;//here
        
        
        
        
        vFrom = GetHitboxPosition(entity, MakeLegitHitscan(entity, pCmd));//here
        
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(local, entity);
        float getdmg = 0.f;
        Autowall::FireBulletData data;
        bool canHit = false;
        
        if(vars.aimbot.autowall)
        {
            getdmg = Autowall::GetDamage(vFrom, true, data);
            canHit = getdmg >= vars.aimbot.mindmg;
        }
        
        // FOV HERE
        
        atTargets = vTo;
        
        if(canHit || isVISIBLE)
        {
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.legitFOV) //here
            {
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    if(vars.aimbot.smooth && !vars.aimbot.spiral) //here
                        pCmd->viewangles = Smooth(vTo, weapon);
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            
        }
        
    }
}


