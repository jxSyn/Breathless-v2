//
//  asuswalls.cpp
//  pwned
//
//  Created by Finn Le var on 8/05/17.
//  Copyright © 2017 vlone.cc. All rights reserved.
//

#include "asuswalls.h"

float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

std::unordered_map<MaterialHandle_t, Color> worldMaterials;
std::unordered_map<MaterialHandle_t, Color> worldMaterials2;

void asuswalls(ClientFrameStage_t stage) {
    
    for (auto i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
    {
        auto pMat = pMatSystem->GetMaterial(i);
        
        if (!pMat)
            continue;
        
        if (strstr(pMat->GetTextureGroupName(), "StaticProp"))
        {
            static auto r_DrawSpecificStaticProp = pCvar->FindVar("r_DrawSpecificStaticProp");
            
            std::string modelName = pMat->GetName();
            
            if (vars.misc.asuswalls)
            {
                r_DrawSpecificStaticProp->SetValue(0);
                pMat->AlphaModulate(vars.misc.asusalpha);
            }
            else
            {
                r_DrawSpecificStaticProp->SetValue(1);
                pMat->ColorModulate(1.f, 1.f, 1.f);
                pMat->AlphaModulate(1.f);
            }
        }
        
        if (strstr(pMat->GetTextureGroupName(), "Particle textures"))
        {
            pMat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, vars.misc.asuswalls);
        }
    }
}

void PerformNightmode()
{
    static bool nightmode_performed = false, nightmode_lastsetting;
    
    if (!pEngine->IsConnected() || !pEngine->IsInGame())
    {
        if (nightmode_performed)
            nightmode_performed = false;
        return;
    }
    
    auto local_player = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!local_player)
        return;
    
    if (!local_player)
    {
        if (nightmode_performed)
            nightmode_performed = false;
        return;
    }
    
    if (nightmode_lastsetting != vars.visuals.nightmode)
    {
        nightmode_lastsetting = vars.visuals.nightmode;
        nightmode_performed = false;
    }
    
    if (!nightmode_performed)
    {
        static ConVar* r_DrawSpecificStaticProp = pCvar->FindVar("r_DrawSpecificStaticProp");
        r_DrawSpecificStaticProp->nFlags &= ~FCVAR_CHEAT;
        
        static ConVar* sv_skyname = pCvar->FindVar("sv_skyname");
        sv_skyname->nFlags &= ~FCVAR_CHEAT;
        
        for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
        {
            IMaterial *mat = pMatSystem->GetMaterial(i);
            
            if (!mat)
                continue;
            
            if (strstr(mat->GetTextureGroupName(), "World"))
            {
                if (vars.visuals.nightmode)
                    mat->ColorModulate(0.08, 0.08, 0.05);
                else
                    mat->ColorModulate(1, 1, 1);
                
                if (vars.visuals.nightmode)
                {
                    sv_skyname->SetValue("sky_csgo_night02");
                    mat->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
                    mat->ColorModulate(0.05, 0.05, 0.05);
                }
                else
                {
                    sv_skyname->SetValue("vertigoblue_hdr");
                    mat->ColorModulate(1.00, 1.00, 1.00);
                }
            }
            else if (strstr(mat->GetTextureGroupName(), "StaticProp"))
            {
                if (vars.visuals.nightmode)
                    mat->ColorModulate(0.28, 0.28, 0.28);
                else
                    mat->ColorModulate(1, 1, 1);
            }
        }
        nightmode_performed = true;
    }
}
                   

