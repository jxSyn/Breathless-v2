#include "skinchanger.h"

int KnifeCT = WEAPON_KNIFE_M9_BAYONET;
int KnifeT = WEAPON_KNIFE_KARAMBIT;
int GloveCT = GLOVE_LEATHER_WRAP;
int GloveT = GLOVE_LEATHER_WRAP;

unordered_map<int, cSkin> cSkinchanger::Skins = unordered_map<int, cSkin>( {
    /* https://github.com/sonicrules11/CSGO-skin-ID-dumper/blob/master/item_index.txt */
    // make_pair(WEAPON, cSkin(Skin, Seed, -1, Stattrak, Entity Quality, (char*)("Name") or nullptr for no name, Wear)),
    make_pair(WEAPON_KNIFE, cSkin(419, -1, KnifeCT, -1, 3, (char*)("Period Blood"), 0.0001f)), // Ruby Doppler
    make_pair(WEAPON_KNIFE_T, cSkin(38, -1, KnifeT, -1, 3, (char*)("I'm faded"), 0.0001f)), // Fade
    // Gloves
    make_pair(GLOVE_CT, cSkin(10021, -1, GloveCT, -1, 3, nullptr, 0.0001f)), //
    make_pair(GLOVE_T, cSkin(10021, -1, GloveT, -1, 3, nullptr, 0.0001f)), //
    // Pistols
    make_pair(WEAPON_CZ75A, cSkin(297, -1, -1, -1, 0, nullptr, 0.0001f)), // Tuxedo
    make_pair(WEAPON_DEAGLE, cSkin(711, -1, -1, -1, 0, nullptr, 0.0001f)), // Code Red
    make_pair(WEAPON_ELITE, cSkin(710, -1, -1, -1, 0, nullptr, 0.0001f)), // Shred
    make_pair(WEAPON_FIVESEVEN, cSkin(44, -1, -1, -1, 0, nullptr, 0.0001f)), // Case Hardended
    make_pair(WEAPON_GLOCK, cSkin(38, -1, -1, -1, 0, nullptr, 0.0001f)), // Fade
    make_pair(WEAPON_HKP2000, cSkin(211, -1, -1, 1337, 0, nullptr, 0.0001f)), // Ocean Foam (P2000)
    make_pair(WEAPON_P250, cSkin(102, -1, -1, -1, 0, nullptr, 0.0001f)), // Whiteout
    make_pair(WEAPON_REVOLVER, cSkin(12, -1, -1, -1, 0, nullptr, 0.0001f)), // Crimson Web
    make_pair(WEAPON_TEC9, cSkin(36, -1, -1, -1, 0, nullptr, 0.0001f)), // Ossified
    make_pair(WEAPON_USP_SILENCER, cSkin(657, -1, -1, -1, 0, nullptr, 0.0001f)), // Blueprint
    // Rifles
    make_pair(WEAPON_AK47, cSkin(316, -1, -1, -1, 0, (char*)("PussyDestroyer15"), 0.0001f)), // Jaguar
    make_pair(WEAPON_AUG, cSkin(455, -1, -1, -1, 0, (char*)("Nico Nico Nii"), 0.0001f)), // Akihabara Accept
    make_pair(WEAPON_AWP, cSkin(279, -1, -1, -1, 0, nullptr, 0.99f)), // Asiimov
    make_pair(WEAPON_FAMAS, cSkin(604, -1, -1, -1, 0, nullptr, 0.0001f)), // Roll Cage
    make_pair(WEAPON_G3SG1, cSkin(606, -1, -1, -1, 0, nullptr, 0.0001f)), // Ventilator
    make_pair(WEAPON_M4A1_SILENCER, cSkin(663, -1, -1, -1, 0, nullptr, 0.0001f)), // Breifing
    make_pair(WEAPON_M4A1, cSkin(695, -1, -1, -1, 0, nullptr, 0.0001f)), // Neo-Noir
    make_pair(WEAPON_SCAR20, cSkin(642, -1, -1, -1, 0, nullptr, 0.0001f)), // Blueprint
    make_pair(WEAPON_SG556, cSkin(200, -1, -1, -1, 0, nullptr, 0.0001f)), // Mayan Dreams
    make_pair(WEAPON_SSG08, cSkin(624, -1, -1, -1, 0, (char*)("Chinese Dragonlore"), 0.0001f)), // Dragonfire
    make_pair(WEAPON_GALILAR, cSkin(661, -1, -1, -1, 0, nullptr, 0.0001f)), // Sugar Rush
    // SMGs
    make_pair(WEAPON_MAC10, cSkin(433, -1, -1, -1, 0, nullptr, 0.0001f)), // Neon Rider
    make_pair(WEAPON_MP7, cSkin(627, -1, -1, -1, 0, nullptr, 0.0001f)), // Cirrus
    make_pair(WEAPON_MP9, cSkin(549, -1, -1, -1, 0, nullptr, 0.0001f)), // Bioleak
    make_pair(WEAPON_P90, cSkin(636, -1, -1, -1, 0, nullptr, 0.0001f)), // Shallow Grave
    make_pair(WEAPON_MP5, cSkin(39, -1, -1, -1, 0, nullptr, 0.0001f)), // Bulldozer
    make_pair(WEAPON_UMP45, cSkin(436, -1, -1, -1, 0, nullptr, 0.0001f)), // Grand Prix
    make_pair(WEAPON_BIZON, cSkin(203, -1, -1, -1, 0, nullptr, 0.0001f)), // Rust Coat
    // Heavy
    make_pair(WEAPON_MAG7, cSkin(666, -1, -1, -1, 0, nullptr, 0.0001f)), // Hard Water
    make_pair(WEAPON_NOVA, cSkin(590, -1, -1, -1, 0, nullptr, 0.0001f)), // Exo
    make_pair(WEAPON_SAWEDOFF, cSkin(638, -1, -1, -1, 0, nullptr, 0.0001f)), // Wasteland Princess
    make_pair(WEAPON_XM1014, cSkin(654, -1, -1, -1, 0, nullptr, 0.0001f)), // Seasons
    make_pair(WEAPON_M249, cSkin(648, -1, -1, -1, 0, nullptr, 0.0001f)), // Emerald Posion Dart
    make_pair(WEAPON_NEGEV, cSkin(483, -1, -1, -1, 0, nullptr, 0.0001f)), // Loudmouth
});

unordered_map<int, const char*> cSkinchanger::ModelList;

cSkinchanger* skinchanger = new cSkinchanger;

void cSkinchanger::FrameStageNotify(ClientFrameStage_t stage) {
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
        pLocalPlayer = (C_BaseEntity*)(pEntList->GetClientEntity(pEngine->GetLocalPlayer()));
        
        if(pLocalPlayer && pLocalPlayer->GetHealth() > 0){
            if(!bInit){
                Init();
                bInit = true;
            }
            ForceSkins();
        }
    }
}

void cSkinchanger::FindModels() {
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl")] = KnifeToModelMatrix[KnifeCT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl")] = KnifeToModelMatrix[KnifeT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_hardknuckle/v_glove_hardknuckle.mdl")] = GloveToModelMatrix[GloveCT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_fingerless/v_glove_fingerless.mdl")] = GloveToModelMatrix[GloveT].c_str();
}

void cSkinchanger::ForceSkins() {
    player_info_t player_info;
    
    if(pEngine->GetPlayerInfo(pLocalPlayer->GetId(), &player_info)){
        
        int* pWeapons = pLocalPlayer->GetWeapons();
        
        C_BaseViewModel* LocalPlayerViewModel = (C_BaseViewModel*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetViewModel());
        
        C_BaseAttributableItem* WeaponViewModel = nullptr;
        
        if(LocalPlayerViewModel)
            WeaponViewModel = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(LocalPlayerViewModel->GetWeapon());
        
        C_BaseCombatWeapon* localWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetActiveWeapon());
        
        if(pWeapons){
            for(int i = 0; pWeapons[i]; i++){
                C_BaseAttributableItem* attributableItem = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(pWeapons[i]);
                if(attributableItem) {
                    short* Definition = attributableItem->GetItemDefinitionIndex();
                    
                    unordered_map<int, cSkin>::iterator SkinIter = (*Definition == WEAPON_KNIFE ? (*Definition == WEAPON_KNIFE ? Skins.find(WEAPON_KNIFE) : Skins.find(WEAPON_KNIFE_T)) : Skins.find(*Definition));
                    
                    if(SkinIter != Skins.end()) {
                        if(*attributableItem->GetOriginalOwnerXuidLow() == player_info.xuidlow && *attributableItem->GetOriginalOwnerXuidHigh() == player_info.xuidhigh){
                            
                            int* model_index = attributableItem->GetModelIndex();
                            
                            unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);
                            
                            if(model_iter != ModelList.end()){
                                *model_index = pModelInfo->GetModelIndex(model_iter->second);
                            }
                            
                            cSkin skin = move(SkinIter->second);
                            
                            if(KnifeCT && (*Definition == WEAPON_KNIFE))
                                *attributableItem->GetItemDefinitionIndex() = KnifeCT;
                            else if(KnifeT && (*Definition == WEAPON_KNIFE_T))
                                *attributableItem->GetItemDefinitionIndex() = KnifeT;
                            
                            if(skin.name) {
                                sprintf(attributableItem->GetCustomName(), "%s", skin.name);
                            }
                            
                            *attributableItem->GetItemIDHigh() = -1;
                            *attributableItem->GetFallbackPaintKit() = skin.Paintkit;
                            *attributableItem->GetFallbackStatTrak() = skin.StatTrack;
                            *attributableItem->GetEntityQuality() = skin.EntityQuality;
                            *attributableItem->GetFallbackSeed() = skin.Seed;
                            *attributableItem->GetFallbackWear() = skin.Wear;
                            *attributableItem->GetAccountID() = player_info.xuidlow;
                            
                            ApplyCustomGloves();
                            Init();
                        }
                    }
                    
                    if (WeaponViewModel && WeaponViewModel == attributableItem) {
                        int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();
                        
                        unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);
                        
                        if (model_iter != ModelList.end()) {
                            *model_index = pModelInfo->GetModelIndex(model_iter->second);
                        }
                    }
                }
            }
            
            if(LocalPlayerViewModel && localWeapon) {
                
                int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();
                
                unordered_map<int, const char*>::iterator model_iter = ModelList.find(*((C_BaseEntity*)localWeapon)->GetModelIndex());
                
                if(model_iter != ModelList.end()){
                    *model_index = pModelInfo->GetModelIndex(model_iter->second);
                }
            }
        }
    }
}

void cSkinchanger::ApplyCustomGloves() {
    
    C_BaseEntity* pLocal = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!pEntList->GetClientEntityFromHandle((void*)pLocal->GetWearables())) {
        for (ClientClass* pClass = pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext) {
            if (pClass->m_ClassID != (int)EClassIds::CEconWearable)
                continue;
            
            int entry = (pEntList->GetHighestEntityIndex() + 1);
            int serial = RandomInt(0x0, 0xFFF);
            
            pClass->m_pCreateFn(entry, serial);
            pLocal->GetWearables()[0] = entry | serial << 16;
            
            glovesUpdated = true;
            
            break;
        }
    }
    
    player_info_t LocalPlayerInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &LocalPlayerInfo);
    
    C_BaseAttributableItem* glove = (C_BaseAttributableItem*)pEntList->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);
    
    if (!glove)
        return;
    
    int* glove_index = glove->GetModelIndex();
    unordered_map<int, const char*>::iterator glove_iter = ModelList.find(*glove_index);
    unordered_map<int, cSkin>::iterator Iter = (pLocal->GetTeam() == TEAM_COUNTER_TERRORIST ? Skins.find(GLOVE_CT) : Skins.find(GLOVE_T));
    cSkin gloveskin = move(Iter->second);
    
    if(glove_iter != ModelList.end())
        *glove_index = pModelInfo->GetModelIndex(glove_iter->second);
    
    if(GloveCT && pLocal->GetTeam() == TEAM_COUNTER_TERRORIST)
        *glove->GetItemDefinitionIndex() = GloveCT;
    if(GloveT && pLocal->GetTeam() == TEAM_TERRORIST)
        *glove->GetItemDefinitionIndex() = GloveT;
    
    *glove->GetItemIDHigh() = -1;
    *glove->GetFallbackPaintKit() = gloveskin.Paintkit;
    *glove->GetFallbackWear() = gloveskin.Wear;
    *glove->GetAccountID() = LocalPlayerInfo.xuidlow;
    
    if(glovesUpdated) {
        glove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
        glovesUpdated = false;
    }
}

void cSkinchanger::Init() {
    ModelList.clear();
    FindModels();
}

void cSkinchanger::FireEventClientSide(IGameEvent *event) {
    if(!strcmp(event->GetName(), "game_newmap")) {
        Init();
    }
}

// Fix Animations (I don't know if any of the new knives have a new animation so I can't update them)
inline const int RandomSequence(int low, int high) {
    return (rand() % (high - low + 1) + low);
}

void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
    CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
    C_BaseViewModel* pViewModel = (C_BaseViewModel*)pStruct;
    
    if(!pViewModel)
        return g_pSequence(pDataConst, pStruct, pOut);
    
    C_BaseEntity* pOwner = (C_BaseEntity*)pEntList->GetClientEntityFromHandle(pViewModel->GetOwner());
    
    if (pViewModel && pOwner) {
        if (pOwner->GetIndex() == pEngine->GetLocalPlayer()) {
            
            const model_t* knife_model = pModelInfo->GetModel(*pViewModel->GetModelIndex());
            const char* model_filename = pModelInfo->GetModelName(knife_model);
            
            int m_nSequence = (int)pData->m_Value.m_Int;
            
            if (!strcmp(model_filename, "models/weapons/v_knife_butterfly.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
                        break;
                    default:
                        m_nSequence++;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_falchion_advanced.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_FALCHION_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence--;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_push.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_DAGGERS_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_LIGHT_MISS1:
                    case SEQUENCE_DEFAULT_LIGHT_MISS2:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_HIT1:
                    case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence += 3;
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence += 2;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_survival_bowie.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_BOWIE_IDLE1;
                        break;
                    default:
                        m_nSequence--;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_ursus.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
                        break;
                    default:
                        m_nSequence++;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_stiletto.mdl")) {
                switch (m_nSequence){
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(12, 13);
                        break;
                }
            } else if(!strcmp(model_filename, "models/weapons/v_knife_widowmaker.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_TALON_LOOKAT1, SEQUENCE_TALON_LOOKAT2);
                        break;
                }
            }
            pData->m_Value.m_Int = m_nSequence;
        }
    }
    return g_pSequence(pData, pStruct, pOut);
}
