#include "../Hacks/dlights.h"

// Thanks @rocco (even though it's from aimtux lmao)

void DLights()
{
    if (!vars.visuals.dlights)
        return;
    
    if (!pEngine->IsInGame())
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer || !localplayer->GetAlive())
        return;
    
   for (int i = 0; i < pEngine->GetMaxClients(); i++)
    {
        C_BaseEntity* player = (C_BaseEntity*) pEntList->GetClientEntity(i);
        
        if (!player)
            continue;
        
        if (player == localplayer)
            continue;

       if (player->GetTeam() != localplayer->GetTeam() && (!vars.visuals.enabled))
       {
            dlight_t* eLight = pEffects->CL_AllocElight(i);
            eLight->origin =  player->GetVecOrigin() + Vector(0.0f, 0.0f, 35.0f);
            eLight->radius = 100.0f;
            eLight->color.r = 255;
            eLight->color.g = 0;
            eLight->color.b = 0;
            eLight->color.exponent = 500.0f; //10.f
            eLight->die = pGlobals->curtime + 0.05f;
            eLight->decay = eLight->radius / 5.0f;
            eLight->key = i;
            
            dlight_t* dLight = pEffects->CL_AllocDlight(i);
            dLight->key = i;
            dLight->color.r = 255;
            dLight->color.g = 0;
            dLight->color.b = 0;
            dLight->color.exponent = 500.0f; //10.f
            dLight->flags = DLIGHT_NO_MODEL_ILLUMINATION;
            dLight->m_Direction = player->GetVecOrigin();
            dLight->origin = player->GetVecOrigin();
            dLight->radius = 1000.0f; //50
            dLight->die = pGlobals->curtime + 0.5f;
            dLight->decay = dLight->radius / 5.0f;
           
       }

    }
    
}
