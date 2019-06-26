#include "../main.h"

void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);

class cSkin{
public:
    cSkin(){}
    cSkin(int paintkit, int seed, int itemDefinition, int stattrack, int EntityQuality, char* szName, float flWear) :
    Paintkit(paintkit), Seed(seed), ItemDefinition(itemDefinition), StatTrack(stattrack), EntityQuality(EntityQuality), name(szName), Wear(flWear){}
    
    int Paintkit = 0;
    int Seed = 0;
    int ItemDefinition = 0;
    int StatTrack = -1;
    int EntityQuality = 0;
    char* name = nullptr;
    float Wear = 0.0001f;
};

class cSkinchanger {
public:
    static unordered_map<int, cSkin> Skins;
    static unordered_map<int, const char*> ModelList;
    
    unordered_map<int, string> KnifeToModelMatrix = unordered_map<int, string>({
        //    {WEAPON_KNIFE_GHOST, "models/weapons/v_knife_ghost.mdl"}, // Ghost Knife
        {WEAPON_KNIFE_BAYONET, "models/weapons/v_knife_bayonet.mdl"}, // Bayonet Knife
        {WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl"}, // Flip Knife
        {WEAPON_KNIFE_GUT, "models/weapons/v_knife_gut.mdl"}, // Gut Knife
        {WEAPON_KNIFE_KARAMBIT, "models/weapons/v_knife_karam.mdl"}, // Karambit Knife
        {WEAPON_KNIFE_M9_BAYONET, "models/weapons/v_knife_m9_bay.mdl"}, // M9 Knife
        {WEAPON_KNIFE_TACTICAL, "models/weapons/v_knife_tactical.mdl"}, // Huntsman Knife
        {WEAPON_KNIFE_FALCHION, "models/weapons/v_knife_falchion_advanced.mdl"}, // Falchion Knife
        {WEAPON_KNIFE_SURVIVAL_BOWIE, "models/weapons/v_knife_survival_bowie.mdl"}, // Bowie Knife
        {WEAPON_KNIFE_BUTTERFLY, "models/weapons/v_knife_butterfly.mdl"}, // Butterfly Knife
        {WEAPON_KNIFE_PUSH, "models/weapons/v_knife_push.mdl"}, // Shadow Daggers
        {WEAPON_KNIFE_URSUS, "models/weapons/v_knife_ursus.mdl"}, // Ursus Knife
        {WEAPON_KNIFE_GYPSY_JACKKNIFE, "models/weapons/v_knife_gypsy_jackknife.mdl"}, // Navaja Knife
        {WEAPON_KNIFE_STILETTO, "models/weapons/v_knife_stiletto.mdl"}, // Stiletto Knife
        {WEAPON_KNIFE_WIDOWMAKER, "models/weapons/v_knife_widowmaker.mdl"}, // Talon Knife
    });
    unordered_map<int, string> GloveToModelMatrix = unordered_map<int, string>({
        {GLOVE_STUDDED_BLOODHOUND, "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"},
        {GLOVE_HYDRA, "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"},
        {GLOVE_SPORTY, "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"},
        {GLOVE_SLICK, "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"},
        {GLOVE_LEATHER_WRAP, "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"},
        {GLOVE_MOTORCYCLE, "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"},
        {GLOVE_SPECIALIST, "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"}
    });
    
    unordered_map<size_t, string> EntityQuality = {
        {0, "Normal"}, // Normal
        {1, "Genuine"}, // Genuine
        {2, "Vintage"}, // Vintage
        {3, "Unusual"}, // Star
        {5, "Community"}, // Commuinity
        {6, "Developer"}, // Valve
        {7, "Self-Made"}, // Protoype
        {8, "Customized"}, // Customized
        {9, "Strange"}, // Stattrak™
        {10, "Completed"}, // Completed
        {12, "Tournament"} // Souvenir
    };
    void FireEventClientSide(IGameEvent* event);
    void FindModels();
    void ForceSkins();
    void FrameStageNotify(ClientFrameStage_t stage);
    void Init();
    void ApplyCustomGloves();
    bool glovesUpdated = false;
    
    C_BaseEntity* pLocalPlayer = nullptr;
    
    bool bInit = false;
};

extern cSkinchanger* skinchanger;
