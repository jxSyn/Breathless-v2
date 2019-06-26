//
//  Config.cpp
//  vHook
//

#include "../main.h"
#include "Config.h"
#include "skins.h"

//to add in new from update, fix resolver(no options just bool), auto stop(modes aswell), the anti aim buttons n shit, hitmarker sound, thirdperson and distance + realangles.

using namespace std;

Config* config = new Config();
Config* skins_cfg = new Config();
SkinList skin;

const char* ConfigName;
string user     = getenv("USER");
string dsk      = "/Users/" + user + "/Desktop/";
string fdr      = "/Users/" + user + "/Desktop/Breathless";
string Legit    = "/Users/" + user + "/Desktop/Breathless/Legit.ini";
string Rage    = "/Users/" + user + "/Desktop/Breathless/Rage.ini";
string Rage2    = "/Users/" + user + "/Desktop/Breathless/HvH.ini";
//string hvh2    = "/Users/" + user + "/Desktop/Breathless/hvh2.ini";
//string hvh3    = "/Users/" + user + "/Desktop/Breathless/hvh3.ini";
string skins    = "/Users/" + user + "/Desktop/Breathless/skins.ini";

bool GetBoolValue(bool Value)
{
    return Value;
}

int GetIntValue(bool Value)
{
    return Value;
}

float GetFloatValue(float Value)
{
    return Value;
}

void Config::getConfig(int ConfigNo) {
    if(ConfigNo == 0) ConfigName = Legit.c_str();
    else if (ConfigNo == 1) ConfigName = Rage.c_str();
    else if (ConfigNo == 2) ConfigName = Rage2.c_str();
}

bool fileExist(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}

void Config::LoadConfig() {
    
    cfg.SetUnicode(true);
    cfg.LoadFile(ConfigName);
    
    // Left Aimbot
    vars.aimbot.enabled     = cfgget_b("Ragebot", "Enabled");
    vars.aimbot.silent      = cfgget_b("Ragebot", "Silent");
    vars.aimbot.FovToPlayer         = cfgget_f("Ragebot", "FOV");
    vars.aimbot.hitbox      = cfgget_f("Ragebot", "Bone");
    vars.aimbot.autowall     = cfgget_b("Ragebot", "Auto Wall");
    vars.aimbot.mindmg     = cfgget_f("Ragebot", "Minimum Damage");
    vars.aimbot.trigger     = cfgget_b("Ragebot", "Trigger");
    vars.aimbot.accuracyhithcance     = cfgget_f("Ragebot", "Minimum Hitchance");
    vars.aimbot.pointscale     = cfgget_f("Ragebot", "Pointscale");
    vars.aimbot.Baim     = cfgget_b("Ragebot", "Baim Under X");
    vars.aimbot.BaimHP     = cfgget_f("Ragebot", "HP");
    vars.misc.fakelag     = cfgget_b("Ragebot", "Fakelag");
    vars.misc.adaptive     = cfgget_b("Ragebot", "Adaptive");
    vars.misc.fakelagtype     = cfgget_f("Ragebot", "Fakelag Type");
    vars.misc.fakelagf     = cfgget_f("Ragebot", "Fakelag Factor");
    //vars.misc.slow_walk_amount     = cfgget_f("Ragebot", "Slow Walk");
    
    
    // Right Aimbot
    vars.aimbot.autoscope      = cfgget_b("Ragebot", "Auto Scope");
    vars.aimbot.autopistol     = cfgget_b("Ragebot", "Auto Pistol");
    vars.aimbot.autocrouch     = cfgget_b("Ragebot", "Auto Crouch");
    vars.aimbot.autoshoot     = cfgget_b("Ragebot", "Auto Shoot");
    vars.aimbot.autocock     = cfgget_b("Ragebot", "Auto Cock");
    vars.aimbot.autostop     = cfgget_b("Ragebot", "Autostop");
    vars.aimbot.autostop_mode     = cfgget_f("Ragebot", "Autostop Mode");
    vars.aimbot.backtrack     = cfgget_b("Ragebot", "Backtrack");
    vars.aimbot.hitscan     = cfgget_b("Ragebot", "Hitscan");
    vars.aimbot.hitscantype     = cfgget_f("Ragebot", "Hitscan Type");
    
    vars.aimbot.Yawresolver     = cfgget_b("Ragebot", "Resolve");
    vars.aimbot.overrideYaw     = cfgget_b("Ragebot", "Override Yaw");
    
    vars.misc.antiaim         = cfgget_b("Ragebot", "Anti-Aim Enabled");
    vars.misc.pitch           = cfgget_b("Ragebot", "Pitch");
    vars.misc.AAenabled       = cfgget_b("Ragebot", "Yaw");
    vars.misc.freestand       = cfgget_b("Ragebot", "Freestand");
    
    //legit
    vars.aimbot.LegitEnabled = cfgget_b("Legitbot", "Enabled");
    vars.aimbot.legitFOV       = cfgget_f("Legitbot", "FOV");
    vars.aimbot.smooth = cfgget_b("Legitbot", "Smoothing");
    vars.aimbot.smoothf       = cfgget_f("Legitbot", "Smoothing Factor");
    vars.aimbot.legitHitscan = cfgget_b("Legitbot", "Target Hitgroup");
    vars.aimbot.legitHitscanType       = cfgget_f("Legitbot", "Hitgroup");
    
    vars.aimbot.LegitRCS = cfgget_b("Legitbot", "Legit Recoil");
    vars.aimbot.LegitRCSx       = cfgget_f("Legitbot", "Recoil Vertical");
    vars.aimbot.LegitRCSy       = cfgget_f("Legitbot", "Recoil Horizontal");
    vars.aimbot.legitBacktrack = cfgget_b("Legitbot", "Legit Backtrack");
    vars.aimbot.legitBacktrackTicks       = cfgget_f("Legitbot", "Ticks");
    
    // Left Visuals
    vars.visuals.enabled    = cfgget_b("Visuals", "Enabled");
    vars.visuals.enemyonly  = cfgget_b("Visuals", "Enemy Only");
    vars.visuals.visonly       = cfgget_b("Visuals", "Vis Only");
    vars.visuals.box   = cfgget_b("Visuals", "Box");
    vars.visuals.name       = cfgget_b("Visuals", "Name");
    vars.visuals.health       = cfgget_b("Visuals", "Health");
    vars.visuals.armour     = cfgget_b("Visuals", "Armour");
    vars.visuals.healthtext    = cfgget_b("Visuals", "Health Text");
    vars.visuals.skeleton       = cfgget_b("Visuals", "Skeleton");
    vars.visuals.snapline       = cfgget_b("Visuals", "Snaplines");
    //  vars.visuals.bombtimer       = cfgget_b("Players", "Bomb Timer");
    
    vars.visuals.chams                = cfgget_b("Visuals", "Chams");
    vars.visuals.handchams       = cfgget_b("Visuals", "Hand Chams");
    vars.visuals.weaponchams       = cfgget_b("Visuals", "Weapon Chams");
    
    vars.visuals.playersType = cfgget_f("Visuals", "Players Type");
    vars.visuals.handsType       = cfgget_f("Visuals", "Hand Type");
    vars.visuals.weaponType       = cfgget_f("Visuals", "Weapon Type");
    
    // Middle Visuals
    vars.visuals.rcrosshair = cfgget_b("Visuals", "Recoil Crosshair");
    vars.visuals.nightmode       = cfgget_b("Visuals", "Night Mode");
    vars.visuals.skinc       = cfgget_b("Visuals", "Skin Changer");
    vars.aimbot.spreadcrosshair = cfgget_b("Visuals", "Spread Crosshair");
    
    vars.visuals.radar = cfgget_b("Visuals", "Radar");
    vars.visuals.backtrackesp       = cfgget_b("Visuals", "Rage Backtrack ESP");
    vars.visuals.legitBacktrackesp       = cfgget_b("Visuals", "Legit Backtrack ESP");
    vars.visuals.grenade       = cfgget_b("Visuals", "Grenade ESP");
    vars.visuals.leftHandKnife  = cfgget_b("Visuals", "Left Hand Knife");
    vars.visuals.nosmoke        = cfgget_b("Visuals", "No Smoke");
    
    vars.visuals.hitmarker      = cfgget_b("Visuals", "Hitmarker");
    vars.visuals.hitenabled      = cfgget_b("Visuals", "Hitmarker Sound");
    vars.visuals.sound           = cfgget_f("Visuals", "Sound");
    vars.misc.noscope           = cfgget_b("Visuals", "No Scope");

    
    // Right Visual
    
    
    
    // Misc Left
    vars.misc.bhop          = cfgget_b("Misc", "Bhop");
    vars.misc.autostrafe          = cfgget_b("Misc", "Auto Strafe");
    vars.misc.cstrafe          = cfgget_b("Misc", "Circle Strafe");
    vars.misc.fovt          = cfgget_b("Misc", "FOV Changer");
    vars.misc.fov           = cfgget_f("Misc", "FOV");
    //vars.misc.showrank      = cfgget_b("Misc", "Show Ranks");
    vars.misc.norecoil      = cfgget_b("Misc", "No Recoil");
    vars.misc.novisual= cfgget_b("Misc", "No Visual Recoil");
    vars.misc.clantag = cfgget_b("Misc", "Clantag");
    vars.misc.showrank       = cfgget_b("Misc", "Show Ranks");
    vars.misc.thirdperson       = cfgget_b("Misc", "Thirdperson");
    vars.misc.tpdistance           = cfgget_f("Misc", "Distance");
    vars.misc.Real       = cfgget_b("Misc", "Show Real Angles");
    
    //   vars.misc.gamesense = cfgget_b("Misc", "skeet.cc");
    //   vars.misc.aimware = cfgget_b("Misc", "aimware.net");
    //  vars.misc.spammer = cfgget_b("Misc", "Chat Spam");
    
    //Misc Right
    vars.misc.worldpaint       = cfgget_b("Misc", "World Paint");
    vars.misc.showspectators       = cfgget_b("Misc", "Spec List");
    vars.misc.antiscreenshot       = cfgget_b("Misc", "Anti Screenshot");
    vars.misc.antiuntrust       = cfgget_b("Misc", "Antiuntrust");
    //    vars.misc.noflash       = cfgget_b("Misc", "No Flash Enable");
    //    vars.misc.flashalpha    = cfgget_f("Misc", "Flash Alpha");
    
    vars.visuals.CTcham_red           = cfgget_f("Colors", "CT Visible Chams.R");
    vars.visuals.CTcham_green         = cfgget_f("Colors", "CT Visible Chams.G");
    vars.visuals.CTcham_blue          = cfgget_f("Colors", "CT Visible Chams.B");
    
    vars.visuals.CTchamhid_red        = cfgget_f("Colors", "CT Hidden Chams.R");
    vars.visuals.CTchamhid_green      = cfgget_f("Colors", "CT Hidden Chams.G");
    vars.visuals.CTchamhid_blue       = cfgget_f("Colors", "CT Hidden Chams.B");
    
    vars.visuals.Tcham_red           = cfgget_f("Colors", "T Visible Chams.R");
    vars.visuals.Tcham_green         = cfgget_f("Colors", "T Visible Chams.G");
    vars.visuals.Tcham_blue          = cfgget_f("Colors", "T Visible Chams.B");
    
    vars.visuals.Tchamhid_red        = cfgget_f("Colors", "T Hidden Chams.R");
    vars.visuals.Tchamhid_green      = cfgget_f("Colors", "T Hidden Chams.G");
    vars.visuals.Tchamhid_blue       = cfgget_f("Colors", "T Hidden Chams.B");
    
    vars.visuals.menu_red           = cfgget_f("Colors", "Menu.R");
    vars.visuals.menu_green         = cfgget_f("Colors", "Menu.G");
    vars.visuals.menu_blue          = cfgget_f("Colors", "Menu.B");
    
    vars.visuals.arm_red           = cfgget_f("Colors", "Arm.R");
    vars.visuals.arm_green         = cfgget_f("Colors", "Arm.G");
    vars.visuals.arm_blue          = cfgget_f("Colors", "Arm.B");
    
    vars.visuals.weapon_red        = cfgget_f("Colors", "Weapon.R");
    vars.visuals.weapon_green      = cfgget_f("Colors", "Weapon.G");
    vars.visuals.weapon_blue       = cfgget_f("Colors", "Weapon.B");
    
    //   Colours
    /*   vars.colors.pchamr      = cfgget_f("Colours", "pChamr");
     vars.colors.pchamg      = cfgget_f("Colours", "pChamg");
     vars.colors.pchamb      = cfgget_f("Colours", "pChamb");
     
     
     vars.colors.boxr        = cfgget_f("Colours", "boxr");
     vars.colors.boxg        = cfgget_f("Colours", "boxg");
     vars.colors.boxb        = cfgget_f("Colours", "boxb");
     
     vars.colors.pignr       = cfgget_f("Colours", "cignr");
     vars.colors.pigng       = cfgget_f("Colours", "cigng");
     vars.colors.pignb       = cfgget_f("Colours", "cignb");
     
     vars.colors.bignr       = cfgget_f("Colours", "bignr");
     vars.colors.bigng       = cfgget_f("Colours", "bigng");
     vars.colors.bignb       = cfgget_f("Colours", "bignb");
     */
    
}



void Config::SaveConfig() {
    
    
    if(!fileExist(dsk.c_str()))
        mkdir(dsk.c_str(), 0775);
    
    if(!fileExist(fdr.c_str()))
        mkdir(fdr.c_str(), 0775);
    
    
    //CSimpleIniA cfg;
    cfg.SetUnicode(true);
    
    // cfg.SetDoubleValue("Bindings", "Aimlock Key", GetFloatValue((int)vars.aimbot.aimKey));
    //cfg.SetDoubleValue("Bindings", "Trigger Key", GetFloatValue((int)vars.aimbot.triggerKey));
    
    // Left Aimbot
    cfg.SetBoolValue("Ragebot", "Enabled", GetBoolValue(vars.aimbot.enabled));
    cfg.SetBoolValue("Ragebot", "Silent", GetBoolValue(vars.aimbot.silent));
    cfg.SetDoubleValue("Ragebot", "FOV", GetFloatValue(vars.aimbot.FovToPlayer));
    cfg.SetDoubleValue("Ragebot", "Bone", GetFloatValue(vars.aimbot.hitbox));
    cfg.SetBoolValue("Ragebot", "Auto Wall", GetBoolValue(vars.aimbot.autowall));
    cfg.SetDoubleValue("Ragebot", "Minimum Damage", GetFloatValue(vars.aimbot.mindmg));
    cfg.SetBoolValue("Ragebot", "Trigger", GetBoolValue(vars.aimbot.trigger));
    cfg.SetDoubleValue("Ragebot", "Minimum Hitchance", GetFloatValue(vars.aimbot.accuracyhithcance));
    cfg.SetDoubleValue("Ragebot", "Pointscale", GetFloatValue(vars.aimbot.pointscale));
    cfg.SetBoolValue("Ragebot", "Baim Under X", GetBoolValue(vars.aimbot.Baim));
    cfg.SetDoubleValue("Ragebot", "HP", GetFloatValue(vars.aimbot.BaimHP));
    cfg.SetBoolValue("Ragebot", "Fakelag", GetBoolValue(vars.misc.fakelag));
    cfg.SetBoolValue("Ragebot", "Adaptive", GetBoolValue(vars.misc.adaptive));
    cfg.SetDoubleValue("Ragebot", "Fakelag Type", GetFloatValue(vars.misc.fakelagtype));
    cfg.SetDoubleValue("Ragebot", "Fakelag Factor", GetFloatValue(vars.misc.fakelagf));
    //cfg.SetDoubleValue("Ragebot", "Slow Walk", GetFloatValue(vars.misc.slow_walk_amount));
    
    
    cfg.SetBoolValue("Ragebot", "Auto Scope", GetBoolValue(vars.aimbot.autoscope));
    cfg.SetBoolValue("Ragebot", "Auto Pistol", GetBoolValue(vars.aimbot.autopistol));
    cfg.SetBoolValue("Ragebot", "Auto Crouch", GetBoolValue(vars.aimbot.autocrouch));
    cfg.SetBoolValue("Ragebot", "Auto Shoot", GetBoolValue(vars.aimbot.autoshoot));
    cfg.SetBoolValue("Ragebot", "Auto Cock", GetBoolValue(vars.aimbot.autocock));
    cfg.SetBoolValue("Ragebot", "Autostop", GetBoolValue(vars.aimbot.autostop));
    cfg.SetDoubleValue("Ragebot", "Autostop Mode", GetFloatValue(vars.aimbot.autostop_mode));
    
    
    
    cfg.SetBoolValue("Ragebot", "Backtrack", GetBoolValue(vars.aimbot.backtrack));
    cfg.SetBoolValue("Ragebot", "Hitscan", GetBoolValue(vars.aimbot.hitscan));
    cfg.SetDoubleValue("Ragebot", "Hitscan Type", GetFloatValue(vars.aimbot.hitscantype));
    
    cfg.SetBoolValue("Ragebot", "Resolve", GetBoolValue(vars.aimbot.Yawresolver));
    cfg.SetBoolValue("Ragebot", "Override Yaw", GetBoolValue(vars.aimbot.overrideYaw));
    
    cfg.SetBoolValue("Ragebot", "Anti-Aim Enabled", GetBoolValue(vars.misc.antiaim));
    cfg.SetBoolValue("Ragebot", "Pitch", GetBoolValue(vars.misc.pitch));
    cfg.SetBoolValue("Ragebot", "Yaw", GetBoolValue(vars.misc.AAenabled));
    cfg.SetBoolValue("Ragebot", "Freestand", GetBoolValue(vars.misc.freestand));
    
    //  cfg.SetBoolValue("Ragebot", "Yaw Resolver", GetBoolValue(vars.aimbot.Yawresolver));
    //  cfg.SetBoolValue("Ragebot", "Autowall", GetBoolValue(vars.aimbot.autowall));
    // Middle Aimbot
    
    // Anti Aim
    
    
    
    
    
    cfg.SetBoolValue("Legitbot", "Enabled", GetBoolValue(vars.aimbot.LegitEnabled));
    cfg.SetDoubleValue("Legitbot", "FOV", GetFloatValue(vars.aimbot.legitFOV));
    cfg.SetBoolValue("Legitbot", "Smoothing", GetBoolValue(vars.aimbot.smooth));
    cfg.SetDoubleValue("Legitbot", "Smoothing Factor", GetFloatValue(vars.aimbot.smoothf));
    cfg.SetBoolValue("Legitbot", "Target Hitgroup", GetBoolValue(vars.aimbot.legitHitscan));
    cfg.SetDoubleValue("Legitbot", "Hitgroup", GetFloatValue(vars.aimbot.legitHitscanType));
    //
    cfg.SetBoolValue("Legitbot", "Legit Recoil", GetBoolValue(vars.aimbot.LegitRCS));
    cfg.SetDoubleValue("Legitbot", "Recoil Vertical", GetFloatValue(vars.aimbot.LegitRCSx));
    cfg.SetDoubleValue("Legitbot", "Recoil Horizontal", GetFloatValue(vars.aimbot.LegitRCSy));
    cfg.SetBoolValue("Legitbot", "Legit Backtrack", GetBoolValue(vars.aimbot.legitBacktrack));
    cfg.SetDoubleValue("Legitbot", "Ticks", GetFloatValue(vars.aimbot.legitBacktrackTicks));
    
    
    
    // Visuals
    cfg.SetBoolValue("Visuals", "Enabled", GetBoolValue(vars.visuals.enabled));
    cfg.SetBoolValue("Visuals", "Enemy Only", GetBoolValue(vars.visuals.enemyonly));
    cfg.SetBoolValue("Visuals", "Vis Only", GetBoolValue(vars.visuals.visonly));
    cfg.SetBoolValue("Visuals", "Box", GetBoolValue(vars.visuals.box));
    cfg.SetBoolValue("Visuals", "Name", GetBoolValue(vars.visuals.name));
    cfg.SetBoolValue("Visuals", "Health", GetBoolValue(vars.visuals.health));
    cfg.SetBoolValue("Visuals", "Armour", GetBoolValue(vars.visuals.armour));
    cfg.SetBoolValue("Visuals", "Health text", GetBoolValue(vars.visuals.healthtext));
    cfg.SetBoolValue("Visuals", "Skeleton", GetBoolValue(vars.visuals.skeleton));
    cfg.SetBoolValue("Visuals", "Snaplines", GetBoolValue(vars.visuals.snapline));
    
    
    cfg.SetBoolValue("Visuals", "Chams", GetBoolValue(vars.visuals.chams));
    cfg.SetBoolValue("Visuals", "Hand Chams", GetBoolValue(vars.visuals.handchams));
    cfg.SetBoolValue("Visuals", "Weapon Chams", GetBoolValue(vars.visuals.weaponchams));
    //     cfg.SetBoolValue("Players", "Weapons", GetBoolValue(vars.visuals.weapons));
    //     cfg.SetBoolValue("Players", "Enemy Only", GetBoolValue(vars.visuals.enemyonly));
    //     cfg.SetBoolValue("Players", "Bomb Timer", GetBoolValue(vars.visuals.bombtimer));
    
    cfg.SetDoubleValue("Visuals", "Hands Type", GetFloatValue(vars.visuals.handsType));
    cfg.SetDoubleValue("Visuals", "Players Type", GetFloatValue(vars.visuals.playersType));
    cfg.SetDoubleValue("Visuals", "Weapons Type", GetFloatValue(vars.visuals.weaponType));
    
    cfg.SetBoolValue("Visuals", "Recoil Crosshair", GetBoolValue(vars.visuals.rcrosshair));
    cfg.SetBoolValue("Visuals", "Night Mode", GetBoolValue(vars.visuals.nightmode));
    cfg.SetBoolValue("Visuals", "Skin Changer", GetBoolValue(vars.visuals.skinc));
    cfg.SetBoolValue("Visuals", "Spread Crosshair", GetBoolValue(vars.aimbot.spreadcrosshair));
    cfg.SetBoolValue("Visuals", "Radar", GetBoolValue(vars.visuals.radar));
    cfg.SetBoolValue("Visuals", "Rage Backtrack ESP", GetBoolValue(vars.visuals.backtrackesp));
    cfg.SetBoolValue("Visuals", "Legit Backtrack ESP", GetBoolValue(vars.visuals.legitBacktrackesp));
    cfg.SetBoolValue("Visuals", "Grenade ESP", GetBoolValue(vars.visuals.grenade));
    cfg.SetBoolValue("Visuals", "Left Hand Knife", GetBoolValue(vars.visuals.leftHandKnife));
    cfg.SetBoolValue("Visuals", "No Smoke", GetBoolValue(vars.visuals.nosmoke));
    
    cfg.SetBoolValue("Visuals", "Hitmarker", GetBoolValue(vars.visuals.hitmarker));
    cfg.SetBoolValue("Visuals", "Hitmarker Sound", GetBoolValue(vars.visuals.hitenabled));
    cfg.SetDoubleValue("Visuals", "Sound", GetFloatValue(vars.visuals.sound));
    cfg.SetBoolValue("Visuals", "No Scope", GetBoolValue(vars.misc.noscope));

    
    
    // Misc
    cfg.SetBoolValue("Misc", "Bhop", GetBoolValue(vars.misc.bhop));
    cfg.SetBoolValue("Misc", "Auto Strafe", GetBoolValue(vars.misc.autostrafe));
    cfg.SetBoolValue("Misc", "Circle Strafe", GetBoolValue(vars.misc.cstrafe));
    cfg.SetBoolValue("Misc", "FOV Changer", GetBoolValue(vars.misc.fovt));
    cfg.SetDoubleValue("Misc", "FOV", GetFloatValue(vars.misc.fov));
    cfg.SetBoolValue("Misc", "No Recoil", GetBoolValue(vars.misc.norecoil));
    cfg.SetBoolValue("Misc", "No Visual Recoil", GetBoolValue(vars.misc.novisual));
    cfg.SetBoolValue("Misc", "Clantag", GetBoolValue(vars.misc.clantag));
    cfg.SetBoolValue("Misc", "Show Ranks", GetBoolValue(vars.misc.showrank));
    
    cfg.SetBoolValue("Misc", "Thirdperson", GetBoolValue(vars.misc.thirdperson));
    cfg.SetDoubleValue("Misc", "Distance", GetFloatValue(vars.misc.tpdistance));
    cfg.SetBoolValue("Misc", "Show Real Angles", GetBoolValue(vars.misc.Real));
    
    
    //cfg.SetBoolValue("Misc", "Airstuck", GetBoolValue(vars.misc.airstuck));
    // cfg.SetBoolValue("Misc", "Show Rank", GetBoolValue(vars.misc.showrank));
    //cfg.SetBoolValue("Misc", "Asus", GetBoolValue(vars.misc.asuswalls));
    // cfg.SetBoolValue("Misc", "No Flash", GetBoolValue(vars.misc.noflash));
    // cfg.SetBoolValue("Misc", "Spammer", GetBoolValue(vars.misc.spammer));
    // cfg.SetBoolValue("Misc", "Skin Changer", GetBoolValue(vars.visuals.skinc));
    
    
    cfg.SetBoolValue("Misc", "World Paint", GetBoolValue(vars.misc.worldpaint));
    cfg.SetBoolValue("Misc", "Spectator List", GetBoolValue(vars.misc.showspectators));
    cfg.SetBoolValue("Misc", "Anti Screenshot", GetBoolValue(vars.misc.antiscreenshot));
    cfg.SetBoolValue("Misc", "Antiuntrust", GetBoolValue(vars.misc.antiuntrust));
    
    
    //Colours
    cfg.SetDoubleValue("Colors", "CT Visible Chams.R", GetFloatValue(vars.visuals.CTcham_red));
    cfg.SetDoubleValue("Colors", "CT Visible Chams.G", GetFloatValue(vars.visuals.CTcham_green));
    cfg.SetDoubleValue("Colors", "CT Visible Chams.B", GetFloatValue(vars.visuals.CTcham_blue));
    
    cfg.SetDoubleValue("Colors", "CT Hidden Chams.R", GetFloatValue(vars.visuals.CTchamhid_red));
    cfg.SetDoubleValue("Colors", "CT Hidden Chams.G", GetFloatValue(vars.visuals.CTchamhid_blue));
    cfg.SetDoubleValue("Colors", "CT Hidden Chams.B", GetFloatValue(vars.visuals.CTchamhid_green));
    
    cfg.SetDoubleValue("Colors", "T Visible Chams.R", GetFloatValue(vars.visuals.Tcham_red));
    cfg.SetDoubleValue("Colors", "T Visible Chams.G", GetFloatValue(vars.visuals.CTcham_green));
    cfg.SetDoubleValue("Colors", "T Visible Chams.B", GetFloatValue(vars.visuals.CTcham_blue));
    
    cfg.SetDoubleValue("Colors", "T Hidden Chams.R", GetFloatValue(vars.visuals.Tchamhid_red));
    cfg.SetDoubleValue("Colors", "T Hidden Chams.G", GetFloatValue(vars.visuals.Tchamhid_blue));
    cfg.SetDoubleValue("Colors", "T Hidden Chams.B", GetFloatValue(vars.visuals.Tchamhid_green));
    
    cfg.SetDoubleValue("Colors", "Menu.R", GetFloatValue(vars.visuals.menu_red));
    cfg.SetDoubleValue("Colors", "Menu.G", GetFloatValue(vars.visuals.menu_green));
    cfg.SetDoubleValue("Colors", "Menu.B", GetFloatValue(vars.visuals.menu_blue));
    
    cfg.SetDoubleValue("Colors", "Arm.R", GetFloatValue(vars.visuals.arm_red));
    cfg.SetDoubleValue("Colors", "Arm.G", GetFloatValue(vars.visuals.arm_green));
    cfg.SetDoubleValue("Colors", "Arm.B", GetFloatValue(vars.visuals.arm_blue));
    
    cfg.SetDoubleValue("Colors", "Weapon.R", GetFloatValue(vars.visuals.weapon_red));
    cfg.SetDoubleValue("Colors", "Weapon.G", GetFloatValue(vars.visuals.weapon_green));
    cfg.SetDoubleValue("Colors", "Weapon.B", GetFloatValue(vars.visuals.weapon_blue));
    
    // AA
    
    
    //    fakelag
    
    
    
    
    cfg.SaveFile(ConfigName);
    
}

void Config::InitSkins() {
    
    if(fileExist(skins.c_str()))
        return;
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("Knife", "CT Knife", GetFloatValue(skin.KnifeCT));
    skins_cfg.SetDoubleValue("Knife", "T Knife", GetFloatValue(skin.KnifeT));
    skins_cfg.SetDoubleValue("Knife", "CT Knife ID", GetFloatValue(skin.CTKnifeID));
    skins_cfg.SetDoubleValue("Knife", "T Knife ID", GetFloatValue(skin.TKnifeID));
    
    skins_cfg.SetDoubleValue("Rifles", "Galil", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("Rifles", "Famas", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("Rifles", "AK47", GetFloatValue(skin.ak47));
    skins_cfg.SetDoubleValue("Rifles", "M4A4", GetFloatValue(skin.m4a4));
    skins_cfg.SetDoubleValue("Rifles", "M4A1S", GetFloatValue(skin.m4a1));
    skins_cfg.SetDoubleValue("Rifles", "Scout", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("Rifles", "SG", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("Rifles", "AUG", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("Rifles", "AWP", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("Rifles", "G3SG1", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("Rifles", "Scar 20", GetFloatValue(skin.scar));
    
    skins_cfg.SetDoubleValue("Pistols", "Glock", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("Pistols", "USP", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("Pistols", "P2000", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("Pistols", "Dual", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("Pistols", "P250", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("Pistols", "Tec 9", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("Pistols", "Five Seven", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("Pistols", "CZ 75", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("Pistols", "Deagle", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("Pistols", "R8", GetFloatValue(skin.revolver));
    
    skins_cfg.SetDoubleValue("SMGs", "Mac 10", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("SMGs", "MP9", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("SMGs", "MP7", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("SMGs", "UMP", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("SMGs", "P90", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("SMGs", "Bizon", GetFloatValue(skin.bizon));
    
    skins_cfg.SetDoubleValue("Heavy", "Nova", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("Heavy", "Sawed off", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("Heavy", "Mag 7", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("Heavy", "XM", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("Heavy", "M249", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("Heavy", "Negev", GetFloatValue(skin.negev));
    
    
    
    skins_cfg.SaveFile(skins.c_str());
    
}


void Config::LoadSkins() {
    
    if(!fileExist(skins.c_str()))
        InitSkins();
    
    skins_cfg.SetUnicode(true);
    skins_cfg.LoadFile(skins.c_str());
    
    skin.KnifeCT    = skin_cfgget_f("Knife", "T Knife");
    skin.KnifeCT   = skin_cfgget_f("Knife", "CT Knife");
    skin.TKnifeID   = skin_cfgget_f("Knife", "T Knife ID");
    skin.CTKnifeID  = skin_cfgget_f("Knife", "CT Knife ID");
    
    skin.galil   = skin_cfgget_f("Rifles", "Galil");
    skin.famas   = skin_cfgget_f("Rifles", "Famas");
    skin.ak47    = skin_cfgget_f("Rifles", "AK47");
    skin.m4a4    = skin_cfgget_f("Rifles", "M4A4");
    skin.m4a1    = skin_cfgget_f("Rifles", "M4A1S");
    skin.scout   = skin_cfgget_f("Rifles", "Scout");
    skin.sg      = skin_cfgget_f("Rifles", "SG");
    skin.aug     = skin_cfgget_f("Rifles", "AUG");
    skin.awp     = skin_cfgget_f("Rifles", "AWP");
    skin.g3      = skin_cfgget_f("Rifles", "G3SG1");
    skin.scar    = skin_cfgget_f("Rifles", "Scar 20");
    
    skin.glock   = skin_cfgget_f("Pistols", "Glock");
    skin.usp     = skin_cfgget_f("Pistols", "USP");
    skin.p2000   = skin_cfgget_f("Pistols", "P2000");
    skin.dual    = skin_cfgget_f("Pistols", "Dual");
    skin.p250    = skin_cfgget_f("Pistols", "P250");
    skin.tec9    = skin_cfgget_f("Pistols", "Tec 9");
    skin.five7   = skin_cfgget_f("Pistols", "Five Seven");
    skin.cz      = skin_cfgget_f("Pistols", "CZ 75");
    skin.deagle  = skin_cfgget_f("Pistols", "Deagle");
    skin.revolver= skin_cfgget_f("Pistols", "R8");
    
    skin.mac10   = skin_cfgget_f("SMGs", "Mac 10");
    skin.mp9     = skin_cfgget_f("SMGs", "MP9");
    skin.mp7     = skin_cfgget_f("SMGs", "MP7");
    skin.ump     = skin_cfgget_f("SMGs", "UMP");
    skin.p90     = skin_cfgget_f("SMGs", "P90");
    skin.bizon   = skin_cfgget_f("SMGs", "Bizon");
    // Heavy
    skin.nova    = skin_cfgget_f("Heavy", "Nova");
    skin.sawed   = skin_cfgget_f("Heavy", "Sawed off");
    skin.mag7    = skin_cfgget_f("Heavy", "Mag 7");
    skin.xm      = skin_cfgget_f("Heavy", "XM");
    skin.m249    = skin_cfgget_f("Heavy", "M249");
    skin.negev   = skin_cfgget_f("Heavy", "Negev");
    
}



bool Config::HasWeaponConfiguration(const char* section) {
    skins_cfg.LoadFile(skins.c_str());
    CSimpleIniA::TNamesDepend sections;
    skins_cfg.GetAllSections(sections);
    sections.sort(CSimpleIniA::Entry::LoadOrder());
    
    for (auto sect : sections) {
        if(!strcmp(section, sect.pItem)) {
            return true;
        }
    }
    
    return false;
}


cSkin Config::GetWeaponConfiguration(const char *section) {
    
    skins_cfg.LoadFile(skins.c_str());
    
    cSkin weapon_config;
    
    weapon_config.Paintkit      = (int)skin_cfgget_f(section, "id");
    weapon_config.Seed          = (int)skin_cfgget_f(section, "seed");
    weapon_config.ItemDefinition= (short)skin_cfgget_f(section, "itemdef");
    
    return weapon_config;
}

