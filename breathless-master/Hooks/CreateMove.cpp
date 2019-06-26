#include "main.h"

#include "../Hacks/aimbot.h"
#include "../Hacks/legit.h"
#include "../Hacks/antiaim.h"
#include "../Hacks/autoshoot.h"
#include "../Hacks/bhop.h"
#include "../Hacks/clantag.h"
#include "../Hacks/spammer.h"
#include "../Hacks/fakewalk.h"
#include "../Hacks/LagComp.h"

Vector tpangles;

void RecoilControl(C_BaseEntity* local, CUserCmd* cmd)
{

    
    Vector punch = local->GetPunchAngles() * 2.f;
    
    if(vars.misc.norecoil)
    {
        if(cmd->buttons & IN_ATTACK)
        {
            
            cmd->viewangles.x -= punch.x;
            cmd->viewangles.y -= punch.y;
        }
        return;
    }
    
    if(vars.aimbot.rcs)
    {
        if(cmd->buttons & IN_ATTACK)
        {
            cmd->viewangles.x -= punch.x * (vars.aimbot.rcsx / 50);
            cmd->viewangles.y -= punch.y * (vars.aimbot.rcsx / 50);
        }
        return;
    }
    
}

string GetLocalName()
{
    player_info_t localInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &localInfo);
    return localInfo.name;
}

void FakeLag(C_BaseEntity* local, CUserCmd* cmd)
{
    if (!vars.misc.fakelag)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (cmd->buttons & IN_ATTACK)
        return;
    
    if(vars.misc.fakelagtype == 1){
        static int choked = 0;
        
        if (choked >= vars.misc.fakelagf) {
            *bSendPacket = true;
            choked = 0;
        } else {
            *bSendPacket = false;
        }
        
        choked++;
    }
}

void hacks(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, Vector& vOldAngles, float& flForwardmove, float& flSidemove) //float& flWall, float& flConor
{
    //set.command_number = cmd->command_number;
    
    //backtracking->Start(local, cmd);
    
    DoAutoStrafe(cmd, local);
    
    DoBhop(cmd, local);
    
    CirlceStrafe(local, cmd, vOldAngles);
    
    FakeLag(local,cmd);
    
    DoAntiaim(cmd, local, weapon);
    
    DoAim(cmd, local, weapon, flForwardmove, flSidemove); // Add some black magic shit.
    
    DoLegitAim(cmd, local, weapon, flForwardmove, flSidemove);
    
    ContinuousPistols(cmd, weapon); // will continously fire pistol when trigger is  held
    
    AutoCock(cmd, weapon);          // Auto Cock
        
    DoSpammer();                    // Spammer
    
    RecoilControl(local, cmd);
    
    Fakewalk(cmd, local); // Fakewalk
    
    if(draw->m_szChangedValue[3].length() > 0 && vars.misc.clantag) // Clantag Changer
        SetClanTag(draw->m_szChangedValue[3].c_str(), "Xanax");
    
}

bool bOnce = false;
bool SendPacket = true;
bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd)
{
    createmoveVMT->GetOriginalMethod<tCreateMove>(25)(thisptr, flSampleInput, cmd);
    
    if(!cmd->command_number)
        return false;
    
    if(!bSendPacket)
        return false;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return false;
    
    if(local->GetLifeState() != 0)
        return false;
    
    if(local->GetHealth() < 1)
        return false;
    
    if(local->GetDormant())
        return false;
    
    if(!bOnce)
    {
        if(draw->m_szCurrentString[2].empty())
        {
            draw->m_szCurrentString[2] = GetLocalName();
        }
        bOnce = true;
    }
    
    C_BaseCombatWeapon* weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return false;
    
    SendPacket = true;
    *bSendPacket = SendPacket;
    
    Vector vOldAngles = cmd->viewangles;
    Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
    Vector qAimAngles;
    
    float forward = cmd->forwardmove;
    float sidemove = cmd->sidemove;
    float upmove = cmd->upmove;
    
    if(pEngine->IsInGame() && pEngine->IsConnected())
    {
        hacks(cmd, local, weapon, vOldAngles, forward, sidemove);
        
        if(local->GetAlive()){
            *bSendPacket = true;
        }
        
        if(*bSendPacket)
            tpangles = cmd->viewangles;
        
        FixMovement(vOldAngles, cmd);
        ClampMoves(forward, sidemove, upmove);
        
        if(vars.misc.enabled && vars.misc.antiuntrust)
        {
            cmd->viewangles.ClampAngles();
        }
    }
    return false;
}

