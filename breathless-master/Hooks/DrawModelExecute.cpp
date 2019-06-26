#include "main.h"

string DirName(string source)
{
    source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}

string GetWorkingPath()
{
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
    proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
    auto dirname = DirName(pathbuf);
    return dirname;
}

bool IsFileExists(const string& name)
{
    int res = access(name.c_str(), R_OK);
    if (res < 0)
    {
        if (errno == ENOENT)
        {
            return false;
        }
        else if (errno == EACCES)
        {
            return true;
        }
        else
        {
            return true;
        }
    }
    return true;
}

void AddMaterial(string filename, string type, bool ignorez, bool wireframe)
{
    if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt")))
    {
        stringstream ss;
        
        ss << "\"" + type + "\"\n" << endl;
        ss << "{\n" << endl;
        ss << "\t\"$basetexture\" \"VGUI/white_additive\"\n" << endl;
        ss << "\t\"$nofog\" \"1\"\n" << endl;
        ss << "\t\"$ignorez\" \"" + to_string(ignorez) + "\"\n" << endl;
        ss << "\t\"$wireframe\" \""+ to_string(wireframe) +"\"\n" << endl;
        ss << "\t\"$halflambert\" \"1\"\n" << endl;
        ss << "}\n" << endl;
        
        ofstream(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt").c_str()) << ss.str();
    }
}

IMaterial* CreateMaterial(bool ignorez, bool wireframe, string szType)
{
    IMaterial* createdMaterial = nullptr;
    
    if(szType == "VertexLitGeneric")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_textured_ignorez").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_textured_ignorez", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_textured_ignorez", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_textured").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_textured", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_textured", TEXTURE_GROUP_MODEL);
        }
    }
    
    
    if(szType == "UnlitGeneric")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_ignorez").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_ignorez", szType, ignorez, wireframe);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_ignorez", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit", szType, ignorez, wireframe);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit", TEXTURE_GROUP_MODEL);
        }
    }
    
    
    if(szType == "WireFrame")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_ignorez_wirefame").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_ignorez_wireframe", szType, ignorez, true);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_ignorez_wireframe", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_wireframe").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_wireframe", szType, ignorez, true);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_wireframe", TEXTURE_GROUP_MODEL);
        }
    }
    
    createdMaterial->IncrementReferenceCount();
    return createdMaterial;
}

void CallOriginalModel(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    modelVMT->GetOriginalMethod<tDrawModelExecute>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
}

void hkDrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    
    static IMaterial* firstLayer = CreateMaterial(false, false, "VertexLitGeneric");
    static IMaterial* secondLayer = CreateMaterial(true, false, "VertexLitGeneric");
    
    static IMaterial* firstLit = CreateMaterial(false, false, "UnlitGeneric");
    static IMaterial* secondLit = CreateMaterial(true, false, "UnlitGeneric");
    
    static IMaterial* firstWire = CreateMaterial(false, true, "WireFrame");
    static IMaterial* secondWire = CreateMaterial(true, true, "WireFrame");
    
    if(pInfo.pModel)
    {
        string pszModel = pModelInfo->GetModelName(pInfo.pModel);
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        {
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
            pModelRender->ForcedMaterialOverride(NULL);
            return;
        }
        
        
        for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
        {
            IMaterial *pMaterial = pMatSystem->GetMaterial(i);
            
            if (!pMaterial)
                continue;
            
            if(!vars.misc.worldpaint)
                continue;
            
            if (strstr(pMaterial->GetTextureGroupName(), TEXTURE_GROUP_WORLD))
            {
                pMaterial->ColorModulate(vars.colors.world);
            }
            
        }
        
        // Weapon Chams
        if(pszModel.find("weapons") != string::npos  && vars.visuals.weaponchams)
        {
            IMaterial* materialCheckFirst = [&]() -> IMaterial*
            {
                if(vars.visuals.weaponType == 0)
                    return firstLit;
                else if(vars.visuals.weaponType == 1)
                    return firstLayer;
                else if (vars.visuals.weaponType == 2)
                    return firstWire;
            }();
            
            materialCheckFirst->ColorModulate(vars.colors.weapon);
            materialCheckFirst->AlphaModulate(vars.visuals.weaponchams_alpha / 255.f);
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
        
        
        // Hand Chams
        if(pszModel.find("arms") != string::npos && vars.visuals.handchams)
        {
            IMaterial* materialCheckFirst = [&]() -> IMaterial*
            {
                if(vars.visuals.handsType == 0)
                    return firstLit;
                else if(vars.visuals.handsType == 1)
                    return firstLayer;
                else if (vars.visuals.handsType == 2)
                    return firstWire;
            }();
            
            materialCheckFirst->ColorModulate(vars.colors.hands);
            materialCheckFirst->AlphaModulate(vars.visuals.handchams_alpha / 255.f);
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
        
        // Player Chams
        if(pszModel.find("models/player") != string::npos && vars.visuals.chams)
        {
            auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
            auto* entity = pEntList->GetClientEntity(pInfo.entity_index);
            
            if(entity)
            {
                if(entity->GetHealth() > 0)
                {
                    
                    Color ColorIgnorez = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.tchams;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.ctchams;
                        else if(pEngine->GetLocalPlayer() == 3)
                            return vars.colors.ctchams;
                    }();
                    
                    Color ColorNonIgnorez = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.tchams_ign;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.ctchams_ign;
                    }();
                    
                    IMaterial* materialCheckFirst = [&]() -> IMaterial*
                    {
                        if(vars.visuals.playersType == 0)
                            return firstLit;
                        else if(vars.visuals.playersType == 1)
                            return firstLayer;
                        else if (vars.visuals.playersType == 2)
                            return firstWire;
                    }();
                    
                    IMaterial* materialCheckSecond = [&]() -> IMaterial*
                    {
                        if(vars.visuals.playersType == 0)
                            return secondLit;
                        else if(vars.visuals.playersType == 1)
                            return secondLayer;
                        else if (vars.visuals.playersType == 2)
                            return secondWire;
                    }();
                    
                    
                    if(vars.visuals.enemyonly && local->GetTeam() == entity->GetTeam())
                    {
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(NULL);
                    }
                    else
                    {
                        if(!vars.visuals.visonly)
                        {
                            materialCheckSecond->ColorModulate(ColorNonIgnorez);
                            materialCheckSecond->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                            pModelRender->ForcedMaterialOverride(materialCheckSecond);
                            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        }
                        
                        materialCheckFirst->ColorModulate(ColorIgnorez);
                        materialCheckFirst->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                        pModelRender->ForcedMaterialOverride(materialCheckFirst);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
    pModelRender->ForcedMaterialOverride(NULL);
}
