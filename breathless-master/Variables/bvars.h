#pragma once

class ccombobox // this class only handles all the open checks for the combo boxes, nothing more
{
public:
    
    // Anti aim
    bool aaY_opend;
    bool aaX_opend;
    bool FaaY_opend;
    // Chams
    bool hands_opend;
    bool weapons_opend;
    bool players_opend;
    bool menucolor_opend;
    // Menu
    bool colors_opend;
    // Misc
    bool FLag_opend;
    bool fakewalk_opend;
    bool hitscanpri_opend;
    bool legithitscanpri_opend;
    bool smoothtype_opend;
    bool hitscan_opend;
    bool clantag_opend;
    bool wpnConfig_opend;
    bool yawResolver_opend;
    bool freestand_opend;
    bool autostop_opend;
    bool chokeshot_opend;
    bool sound_opend;
    // For aa corrections
    bool playerlist_opend_x[64];
    bool playerlist_opend_y[64];
    // config shit
    bool mCol_opend;
    bool cfg_opend;
    
    //wpn Configs
    bool rifleTargetHitbox_opend;
    bool smgTargetHitbox_opend;
    bool sniperTargetHitbox_opend;
    bool pistolTargetHitbox_opend;
    
    
    // For text input
    bool misc_clantag, misc_name, misc_changename;
    
};

class cVariables : public ccombobox
{
public:
    
    bool menu               = false;
    bool watermark          = true;
    int  buttonPadding      = 24;
    int  playerTab          = 0;
    int  inputIndex         = 0;
    bool cfgInit = false;
    
    class cAimbot
    {
    public:
        
        bool enabled    = false;        // Enable
        bool silent     = false;        // Silent Aim ob
        int  FovToPlayer         = 0.f;          // Aimbot Fov
        int  hitbox      = 0;           // Hitbox
        int  pointscale  = 55;           // Pointscale
        int multipoint   = 0;
        bool ChokeShot   = false;
        bool autoknife  = false;
        // bool trigger    = false;         // Will shoot when an enemy is in your crosshair
        bool prediction = false;        // Player prediction
        bool autowall   = false;        // Shoots through walls if calulated damage is higher than set amount
        int accuracyhithcance = 0;     // Hitchance Accuacry
        int hitchancevalue = 0;
        int  mindmg      = 0;          // Autowall min damage
        bool autoshoot  = false;        // Shoots for you
        bool autoscope  = false;        // Autoscope
        bool autopistol = false;        // Pistol is like AK
        bool autocock   = false;        // Auto Revovler
        bool autocrouch = false;        // Crouch when something is in fov
        bool autozeus   = false;         // Crouch when something is in fov
        bool rcs        = false;        // Recoil control system
        int rcsx        = 0;            // Recoil control
        float rcsy        = 0.f;
        bool hitscan    = false;         // Hitscan
        int jitter = 0;
        int hitscantype = 0;            // HItscan Types
        int lbybreakshit = 0;
        bool flip_bool  = false;
        bool walldetection = false;
        bool fakewalk   = false;
        bool lbyinfo  = false;
        int lbyInfoRange = 80;
        int fakewalktype = 0;         // Fakewalk types
        int BetaPacketChoke = 0;
        bool backtrack  = false;
        bool legitBacktrack = false;
        int legitBacktrackTicks = 0;
        int freestandangle = 0;
        int freestandmode = 0;
        bool salting        = false;
        float saltingmultiplier = 0.f;
        int smoothtype = 0;
        bool spiral     = false;
        
        int on_shot_aa_type = 0;
        
        bool autostop = false;
        int autostop_mode = 0;
        bool stop_inbetween_shots = false;
        
        bool Baim       = false;        // Baim
        int BaimHP      = 60;           // Baim X HP
        bool Baimkey    = true;         // Baim on key mouse 5
        int baimafterXshot = 0;         // Baim After [x] shots
        
        float spiralx   = 1.f;
        float spiraly   = 1.f;
        bool FakeLagFix = true;
        bool spreadcrosshair = false;
        bool Yawresolver= false;        // Resolver
        int yresolve    = 1;            // different resolver
        bool overrideYaw = false;
        
        bool autoslow = false;
        
        
        bool LegitEnabled = false;
        bool legitHitscan = false;
        float legitFOV = 0.f;
        bool smooth        = false;
        float smoothf    = 1.f;
        bool LegitRCS = false;
        float LegitRCSx = 0.f;
        float LegitRCSy = 0.f;
        int legitHitscanType = 0;
        
        bool trigger     = false;             // Enable Trigger
        int triggerKey   = 111;                // Change Trigger KEy
        bool delay       = false;             // Trigger Delay
        int lastRoll     = 0;
        int lowBound     = 0;                 // Low Trigger delay
        int highBound    = 0;                 // Max trigger Delay
        int triggerHitchance = 0;
        bool LocalAirCheck = false;
        bool TargetAirCheck = false;
        
        bool fakelag_prediction = false;
    }aimbot;
    
    class cAimbotCFG
    {
    public:
        
        bool enabled  = false;
        float  FovToPlayer         = 0.f;          // Aimbot Fov
        int  hitbox      = 0;           // Hitbox
        int fovType = 0;
        
        /*--------------------------------------------------Rifles--------------------------------------------------------------*/
        
        float  rifleFov         = 0.f;
        bool rifleRCS        = false;
        float rifleRCSx        = 0.f;
        float rifleRCSy        = 0.f;
        bool Hitscan    = false;
        int rifleTargetHitbox = 0;
        int hitscanType = 0;
        bool rifleSmooth        = false;
        float rifleSmoothf    = 1.f;
        
        /*---------------------------------------------------SMGs---------------------------------------------------------------*/
        
        float  smgFov         = 0.f;
        bool smgRCS        = false;
        float smgRCSx        = 0.f;
        float smgRCSy        = 0.f;
        int smgTargetHitbox = 0;
        bool smgSmooth        = false;
        float smgSmoothf    = 1.f;
        
        /*-------------------------------------------------Snipers--------------------------------------------------------------*/
        float  sniperFov         = 0.f;
        bool sniperRCS        = false;
        float sniperRCSx        = 0.f;
        float sniperRCSy        = 0.f;
        int sniperTargetHitbox = 0;
        bool sniperSmooth        = false;
        float sniperSmoothf    = 1.f;
        
        /*-------------------------------------------------Pistols--------------------------------------------------------------*/
        
        float  pistolFov         = 0.f;
        bool pistolRCS        = false;
        float pistolRCSx        = 0.f;
        float pistolRCSy        = 0.f;
        int pistolTargetHitbox = 0;
        bool pistolSmooth        = false;
        float pistolSmoothf    = 1.f;
        
        /*------------------------------------------------End Aimbot------------------------------------------------------------*/
        
        
        //        int smoothtype = 0;
        bool spiral     = false;
        float spiralx   = 1.f;
        float spiraly   = 1.f;
        
        int activeWeaponCfg = 0;
        
    }wpnConfig;
    
    class cGrenade
    {
    public:
        bool enabled = false;
        bool onlyMatchingInfos = true;
        bool aimAssist = false;
        int aimDistance = 75;
        int aimFov = 45;
        int aimStep = 5;
        
    }GrenadeHelper;
    
    class cVisuals
    {
    public:
        
        bool GrenadePrediction = false;
        
        bool enabled    = false;        // Enable
        bool enemyonly  = true;        // Enemy only
        bool visonly    = false;        // Visual only
        bool box        = false;        // Box ESP
        bool name       = false;        // Name ESP
        bool health     = false;        // Health Bar
        bool healthtext = false;        // Health Text
        bool armour     = false;        // Armour Bar
        bool skeleton   = false;        // Skeleton ESP
        bool snapline   = false;        // Snaplines obv
        bool dlights    = false;        // Dlight
        bool rcrosshair = false;        // Recoil Crosshair (Shows but doesn't move)
        bool scrosshair = false;        // Sniper Crosshair
        bool defusing   = true;        // Defusing ESP
        bool rescuing   = false;        // Hostage rescue and carrying esp
        bool scoped     = false;        // Scoped ESP
        bool grenade    = false;
        bool backtrackesp = false;
        bool bulletTracers = false;
        int bulletTraceLength = 0;
        int targethitbox = 0;
        bool bombtimer  = true;
        bool active     = false;
        bool skinc      = false;
        bool radar      = false;
        bool nightmode      = false;
        int menupcolor = 4;
        bool eyethings = false;
        bool offscreenESP = false;
        int offscreenESPRange = 0;
        bool legitBacktrackesp = false;
        bool antiaim_indicator = false;
        bool antiaim_direction = false;
        
        int colour_r = 0;
        int colour_g = 0;
        int colour_b = 0;
        int colour_a = 0;
        
        bool hitmarker  = true;               // Hitmarkers
        int duration    = 1500;               //2000
        int HMinnerGap  = 3;                  //5
        int HMsize      = 8;                  //16
        bool HMDamage   = true;
        bool allies     = true;
        bool enemies    = true;
        
        bool hitenabled;
        int sound;
        
        bool leftHandKnife = false;
        bool nosmoke    = false;
        
        // Chams
        bool chams      = true;        // Player Chams
        bool handchams  = false;         // Handchams obv
        bool weaponchams= false;         // Weapon chams obv
        int weaponType  = 1;            // Weapon Type 0 - Lit 1 - Texture 2 - Wireframe
        int handsType   = 1;            // Hand   Type 0 - Lit 1 - Texture 2 - Wireframe
        int playersType = 1;            // Player Type 0 - Lit 1 - Texture
        
        int weaponchams_alpha   = 255;  // Weapon Chams Alpha / opacity
        int handchams_alpha     = 255;  // Hand   Chams Alpha / opacity
        int playerchams_alpha   = 255;  // Player Chams Alpha / opacity
        
        bool watermark = true;
        bool fovcircle = false;
        
        bool fakelagchams = false;
        
        int menu_red = 0;
        int menu_green = 0;
        int menu_blue = 0;
        int menu_alpha = 0;
        
        int CTcham_red = 0;
        int CTcham_green = 0;
        int CTcham_blue = 0;
        int CTcham_alpha = 0;
        
        int Tcham_red = 0;
        int Tcham_green = 0;
        int Tcham_blue = 0;
        int Tcham_alpha = 0;
        
        int CTchamhid_red = 0;
        int CTchamhid_green = 0;
        int CTchamhid_blue = 0;
        int CTchamhid_alpha = 0;
        
        int Tchamhid_red = 0;
        int Tchamhid_green = 0;
        int Tchamhid_blue = 0;
        int Tchamhid_alpha = 0;
        
        int weapon_red = 0;
        int weapon_green = 0;
        int weapon_blue = 0;
        int weapon_alpha = 0;
        
        
        int arm_red = 0;
        int arm_green = 0;
        int arm_blue = 0;
        int arm_alpha = 0;
        
        int fov_arrows_esp_color_r = 0;
        int fov_arrows_esp_color_g = 0;
        int fov_arrows_esp_color_b = 0;
        
        bool fov_arrows_always_indicate = false;
        int fov_arrows_enemy_distance   = 0;
        int fov_arrows_enemy_size       = 0;
        
        
        
    }visuals;
    
    class cMisc
    {
    public:
        
        bool enabled        = true;     // Enabled
        bool antiuntrust    = true;     // Anti Untrust KEEP ON AT ALL TIMES UNLESS YOU KNOW WHAT YOURE DOING
        bool norecoil       = false;    // Basically RCS without slider
        bool novisual       = false;    // No visual recoil ofc
        bool bhop           = false;    // BunnyHop
        bool autostrafe     = false;    // Strafes for you ofc
        bool cstrafe        = false;    // Circle strafes
        bool airstuck       = false;    // Airstuck
        bool fovt           = false;    // Fov Changer Enabled
        int fov             = 5;       // FOV changer
        bool clantag        = false;    // Clantag changer
        bool showrank       = true;     // Show everyboys rank in MM
        bool spammer        = false;    // Chat spammer
        bool noflash        = false;     // Disabled flashbangs
        int flashalpha      = 0.f;      // How "flashed" you are
        bool noscope        = false;     // Noscope
        bool asuswalls      = false;
        float asusalpha      = .0;

        
        bool adaptive = false;
        int clantagtype     = 0;
        bool setupConfigs = false;
        
        bool slow_walk = false;
        int slow_walk_amount = 0;
        
        // Choke movment
        bool fakeduck       = true;            // Fakeduck
        bool fakewalk       = true;            // Fakewalk
        int spike           = 0;               // Fakelag spike when so and so, shooting, peek of jump, peeking enemy
        bool fakelag        = false;           // Fakelag
        int fakelagf        = 0.f;             // Fakelag Factor
        int fakelagfmoving  = 0.f;             // Moving
        int fakelagfair     = 0.f;             // Air
        int fakelagtype     = 0.f;             // Different fakelag types
        
        
        bool AAenabled = false;
        bool freestand = false;
        bool pitch = false;
        
        bool thirdperson    = false;          // Third person enabled
        int tpdistance      = 0;              // Thirdperson distance
        bool Real           = true;          // Real Angles
        
        
        
        bool worldpaint     = false;    // World Paint
        bool changesky      = false;    // Changes Sky
        bool antiscreenshot = false;    // Anti screenshot
        bool showspectators = false;    // Spectator List
        // AntiAim
        bool antiaim        = false;    // Anti aims / "spinbot"
        //bool thirdpersonmode= true;    // Thirdperson
        bool attargets      = false;    // AtTargets ofc
        bool fakeaa         = false;    // Fake anti aim
        int aaY             = 0;        // Y AntiAim
        int aaX             = 0;        // X AntiAim
        int FaaY            = 0;        // Y Fake anti aim (Thnx Ziwiiz)
        int customaa        = 0;        // Custom Pitch
        int fakeyaw         = 180;      // Fake Y
        int realyaw         = 20;       // Real Y
        bool edge           = false;
        bool antiResolverFlip= false;   //lby flip
        
        bool memewalk = false;
        
    }misc;
    
    class cColors
    {
    public:
        
        int combo   = 0;
        
        // Cham ESP
        Color ctchams;
        Color tchams;
        
        Color ctchams_ign;
        Color tchams_ign;
        
        Color tbox;
        Color tbox_ign;
        
        Color ctbox;
        Color ctbox_ign;
        
        Color world;
        
        //Hitmarker Colour
        Color HitMarker;
        
        Color hands;
        Color weapon;
        
        Color CTchams_red;
        Color CThams_green;
        Color CTchams_blue;
        
        Color Tchams_red;
        Color Tchams_green;
        Color Tchams_blue;
        
        Color CTchamshid_red;
        Color CThamshid_green;
        Color CTchamshid_blue;
        
        Color Tchamshid_red;
        Color Tchamshid_green;
        Color Tchamshid_blue;
        
        Color chamshid_alpha;
        
        Color chams_alpha;
        
        Color scope;
        Color sky;
        
        Color menu;
        
        Color arrow;
        
        Color aimDot;
        Color aimLine;
        Color infoHE;
        Color infoMolotov;
        Color infoSmoke;
        Color infoFlash;
        
    }colors;
    
};

struct Corrections
{
    float x, y;
    bool whitelist;
    bool resolved;
    bool baim;
    
    int dropdown_x = 0;
    int dropdown_y = 0;
};

/*------------------------------------------------------TODO------------------------------------------------------------*/
/*
 seperate backtrack for rage and legit, setup ticks for legit backtrack and name other rage backtrack
 
 */
/*------------------------------------------------------TODO------------------------------------------------------------*/

extern cVariables vars;
extern Corrections gCorrections[64];

