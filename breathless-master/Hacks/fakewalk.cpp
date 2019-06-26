//
//  fakewalk.cpp
//  vHook
//
//  Created by Warlauke on 10/20/17.
//  Copyright © 2017 ViKiNG. All rights reserved.
//

#include "fakewalk.h" // Pasted from JingWare

//
//  fakewalk.cpp
//  vHook
//
//  Created by Warlauke on 10/20/17.
//  Copyright © 2017 ViKiNG. All rights reserved.
//

#include "fakewalk.h" // Pasted from JingWare

void Fakewalk(CUserCmd* cmd, C_BaseEntity* local)
{
    
    if(!vars.aimbot.fakewalk)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    
    if(!pInputSystem->IsButtonDown(MOUSE_4))
        return;
    
    if(vars.aimbot.fakewalktype == 1){
        static int iChoked = -1;
        iChoked++;
        
        if (iChoked < 3)
        {
            *bSendPacket = false;
            cmd->tick_count += 10;
            cmd += 7 + cmd->tick_count % 2 ? 0 : 1;
            cmd->forwardmove = cmd->sidemove = 0.f;
        }else{
            *bSendPacket = true;
            iChoked = -1;
            pGlobals->frametime *= (local->GetVelocity().Length2D()) / 1.f;
            cmd->buttons |= local->GetMoveType() == IN_FORWARD;
        }
    }
    
    if(vars.aimbot.fakewalktype == 2){
        static int iChoked = 0;
        
        iChoked = iChoked > 7  ? 0 : iChoked + 1;
        cmd->forwardmove = iChoked < 2 || iChoked > 5 ? 0 : cmd->forwardmove;
        cmd->sidemove = iChoked < 2 || iChoked > 5 ? 0 : cmd->sidemove;
        
        *bSendPacket = iChoked < 1;
    }
    
    if(vars.aimbot.fakewalktype == 3){
        static int iChoked = -1;
        iChoked++;
        
        if (iChoked < 1)
        {
            *bSendPacket = false;
            cmd->tick_count += 555;
            cmd->command_number += 7 + cmd->tick_count % 10 ? 0 : 1; // 5
            cmd->forwardmove = cmd->sidemove = 0.f;
        }
        else
        {
            *bSendPacket = true;
            iChoked = -1;
            pGlobals->frametime *= (local->GetVelocity().Length2D()) / 5.f; // 10
            cmd->buttons |= local->GetMoveType() == IN_FORWARD;
        }
    }
    
}

