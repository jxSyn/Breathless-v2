#include "main.h"
#include "skinchanger.h"
#include "asuswalls.h"
#include "LagComp.h"

void RemoveFlash(ClientFrameStage_t stage)
{
    if (!pEngine->IsInGame())
        return;
    
    if(!vars.misc.noflash)
        return;
    
    if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return;
    
    if (vars.misc.noflash)
    {
        *localplayer->GetFlashMaxAlpha() = 255.0f - vars.misc.flashalpha;
    }
    else
    {
        *localplayer->GetFlashMaxAlpha() = 255.0f;
    }
}

void hkFrameStage(void* thisptr, ClientFrameStage_t curStage)
{
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return;
    
    Vector* PointerPunch    = nullptr;
    Vector* PointerView     = nullptr;
    
    Vector VecPunch, VecView;
    
    if(vars.misc.Real)
    {
        if (curStage == ClientFrameStage_t::FRAME_RENDER_START && (pEngine->IsConnected() && pEngine->IsInGame()))
        {

            
        }
        
    }
    
    if(vars.visuals.skinc) {
         skinchanger->FrameStageNotify(curStage);
    }
    
    if(vars.misc.asuswalls)
        asuswalls(curStage);
    
    if(curStage == FRAME_RENDER_START && local)
    {
        if(vars.misc.Real)
        {
            if(pEngine->IsConnected() && pEngine->IsInGame())
            {
                if(local->GetLifeState() == LIFE_ALIVE)
                {
                    *reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(local) + offsets.DT_BasePlayer.deadflag + 0x4) = tpangles;
                }
            }
            
        }
        
        if(vars.misc.novisual)
        {
            if(local->GetLifeState() == LIFE_ALIVE)
            {
                PointerPunch = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_aimPunchAngle);
                PointerView = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_viewPunchAngle);
                
                VecPunch = *PointerPunch;
                VecView = *PointerView;
                
                PointerPunch->Init();
                PointerView->Init();
            }
            
        }
        
    }
    
    
    {   // Call functions here just so its cleaner
        RemoveFlash(curStage);
   
    
    
        
        
    }
    
    clientVMT->GetOriginalMethod<tFrameStage>(37)(thisptr, curStage);
    
    
    
    if(vars.aimbot.enabled && vars.aimbot.Yawresolver && curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        for(int i = 1; i < 64; i++)
        {
            auto* entity = pEntList->GetClientEntity(i);
            
            if(!entity)
                continue;
            
            if(!entity->GetAlive())
                continue;
            
            if(entity->GetImmune())
                continue;
            
            if(entity->GetDormant())
                continue;
            
            if(entity == local)
                continue;
            
            //backtracking->Store(entity);
            
            //*(float*)((uintptr_t)entity + offsets.DT_BasePlayer.m_angRotation1) = AAA_Pitch(entity);
            *(float*)((uintptr_t)entity + offsets.DT_BasePlayer.m_angRotation2) = AAA_Yaw(entity);
        }
        
    }
    
    if(PointerPunch && PointerView)
    {
        *PointerPunch   = VecPunch;
        *PointerView    = VecView;
    }
    
}
