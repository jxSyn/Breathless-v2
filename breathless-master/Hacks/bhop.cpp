#include "bhop.h"

void DoBhop(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.bhop)
        return;
    
    static bool shouldJump = false;
    static bool shouldFake = false;
    
    if (shouldFake && !shouldJump)
    {
        
        cmd->buttons |= IN_JUMP;
        shouldFake = false;
        
    }
    else if (cmd->buttons & IN_JUMP)
    {
        
        if (local->GetFlags() & FL_ONGROUND)
        {
            
            shouldFake = false;
            shouldJump = false;
            
        }
        else
        {
            
            cmd->buttons &= ~IN_JUMP;
            shouldJump = false;
            
        }
        
    }
    else
    {
        
        shouldJump = false;
        shouldFake = false;
        
    }
    
}


void DoAutoStrafe(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.autostrafe)
        return;
    
    if (cmd->buttons & IN_JUMP && !(local->GetFlags() & FL_ONGROUND))
    {
        
        if (local->GetVelocity().Length2D() == 0 && (cmd->forwardmove == 0 && cmd->sidemove == 0))
        {
            
            cmd->forwardmove = 450.f;
            
        }
        else if (cmd->forwardmove == 0 && cmd->sidemove == 0)
        {
            
            if (cmd->mousedx > 0 || cmd->mousedx < -0)
            {
                
                cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
                
            }
            else
            {
                
                float temp1 = 5850.f / local->GetVelocity().Length2D();
                cmd->forwardmove = temp1;
                
                if (cmd->forwardmove > 450)
                    cmd->forwardmove = 450;
                    
                float temp = 450 - (temp1 - cmd->forwardmove);
                    
                if (temp < 450)
                    temp = 450;
                        
                cmd->sidemove = (cmd->command_number % 2) == 0 ? -temp : temp;
                        
            }
            
        }
        
    }
    
}




bool CircleDone = false, JustStarted = true;
void CirlceStrafe(C_BaseEntity *localPlayer, CUserCmd *cmd, Vector &oldAngles)
{
    if(!vars.misc.cstrafe)
        return;
    
    static int Angle = 0;
    
    if (oldAngles.y - Angle > 360)
        Angle -= 360;
    
    static bool shouldspin  = false;
    static bool enabled     = false;
    static bool check       = false;
    
    if (pInputSystem->IsButtonDown(KEY_PERIOD))
    {
        if (!check)
            enabled = !enabled;
        check = true;
    }
    else
    {
        check = false;
    }
    
    if (enabled)
    {
        shouldspin = true;
        cmd->buttons |= IN_JUMP;
        cmd->buttons |= IN_DUCK;
    }
    
    if (shouldspin)
    {
        Vector Dir;
        AngleVectors(Vector(0, Angle, 0), &Dir);
        Dir *= 8218;
        
        Ray_t ray;
        CTraceFilterWorldOnly filter;
        trace_t trace;
        
        ray.Init(localPlayer->GetEyePosition(), localPlayer->GetVecOrigin() + Dir);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        auto temp = 3.4f / ((trace.endpos - localPlayer->GetVecOrigin()).Length() / 100.f);
        
        if (temp < 3.4f)
            temp = 3.4f;
        
        if (enabled)
        {
            Angle += temp;
            cmd->sidemove = -450;
        }
        else
        {
            if (oldAngles.y - Angle < temp)
            {
                Angle = oldAngles.y;
                shouldspin = false;
            }
            else
            {
                Angle += temp;
            }
        }
        oldAngles.y = Angle;
    }
    else
    {
        Angle = oldAngles.y;
    }
}



