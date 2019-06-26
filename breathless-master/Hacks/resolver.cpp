#include "main.h"

RecvVarProxyFn OldProxy_Y; //OldProxy_X;

float AAA_Yaw(C_BaseEntity* entity)
{
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;

    
    bool IsMovingOnInAir = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        !(entity->GetFlags() & FL_ONGROUND)
    };
    
    bool Standing = {
        (entity->GetFlags() & FL_ONGROUND && entity->GetVelocity().Length2D() == 0.f)
    };
    
    bool MovingOnGround = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        entity->GetVelocity().Length2D() > 45.f && entity->GetFlags() & FL_ONGROUND
    };
    
    // Shit Fake Walk dectection
    bool maybeFakeWalking = {
    MovingOnGround && entity->GetVelocity().Length2D() < 36.0f
    };
    
    if (vars.aimbot.Yawresolver) {
        int i = entity->GetIndex();
        static float stored_lby[64];
        static float moving_lby[64];
        static bool bLowerBodyIsUpdated;
        if (entity->GetLowerBodyYawTarget() != stored_lby[i]) bLowerBodyIsUpdated = true;
        else bLowerBodyIsUpdated = false;
        
        if (bLowerBodyIsUpdated)
        {
            stored_lby[i] = entity->GetLowerBodyYawTarget();
        }
        
        if(Standing){
            angle = (rand() % 2) ?
            stored_lby[i] - 35:
            stored_lby[i] + 35;
        }
        else if(MovingOnGround){
            angle = entity->GetLowerBodyYawTarget();
            moving_lby[i] = entity->GetLowerBodyYawTarget();
        }
        else if(maybeFakeWalking){
            angle = (rand() % 2) ?
            moving_lby[i] - 15:
            moving_lby[i] + 15;
        }
        else if(IsMovingOnInAir){
            angle = stored_lby[i];
        }
        else{
            angle = entity->GetLowerBodyYawTarget();
        }
    }
}

void FixYaw(const CRecvProxyData *pData, void *pStruct, void *pOut) {
    float flYaw = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].y = flYaw;
    
    OldProxy_Y(pData, pStruct, pOut);
}
