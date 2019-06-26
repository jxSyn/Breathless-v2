#include "main.h"

#include "esp.h"
#include "../Hacks/autowall.h"
#include "hitmarker.h"
void DrawSkeleton(C_BaseEntity* pEntity, Color color){
    
studiohdr_t* pStudioModel = pModelInfo->GetStudioModel( pEntity->GetModel() );

if ( pStudioModel ) {
    
    static matrix3x4_t pBoneToWorldOut[128];
    
    if ( pEntity->SetupBones( pBoneToWorldOut, 128, 256, 0) )
    {
        for ( int i = 0; i < pStudioModel->numbones; i++ )
        {
            mstudiobone_t* pBone = pStudioModel->pBone( i );
            
            if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
                continue;
            
            Vector vBone1 = pEntity->GetBonePosition(i);
            Vector vBoneOut1;
            
            Vector vBone2 = pEntity->GetBonePosition(pBone->parent);
            Vector vBoneOut2;
            
            if(WorldToScreen(vBone1, vBoneOut1) && WorldToScreen(vBone2, vBoneOut2)) {
                draw->drawline(vBoneOut1.x, vBoneOut1.y, vBoneOut2.x, vBoneOut2.y, color);
            }
        }
    }
}
}


Color GetColorBase(Color& col)
{
    return Color(col.r(), col.g(), col.b(), 255);
}



void DrawHealthbar(int x, int y, int w, int h, int health, Color color)
{
    if(health > 100)
    {
        health = 100;
    }
    int hw = h - ((h) * health) / 100;
    draw->fillrgba(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    draw->fillrgba(x, y + hw - 1, w, h - hw + 2, color);
    draw->drawbox(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    
    
}

void box3d(C_BaseEntity* entity, Color color) {
    
    Vector vOrigin = entity->GetVecOrigin();
    Vector min = entity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = entity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] = { Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(min.x, min.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(max.x, max.y, max.z),
        Vector(max.x, min.y, max.z) };
    
    int edges[12][2] = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
    };
    
    for (auto it : edges) {
        Vector p1, p2;
        if (pOverlay->ScreenPosition(points[it[0]], p1) || pOverlay->ScreenPosition(points[it[1]], p2))
            return;
        
    }
}

/*void cantiaim_indicator(C_BaseEntity* local)
{
    if (!vars.visuals.antiaiminfos)
        return;
    
    if (!local)
        return;
    
    // TODO: color pickers
    static const auto real_color = Color(255, 0, 0, 255);
    static const auto fake_color = Color(0, 0, 255, 255);
    static const auto lby_color = Color(0, 255, 0, 255);
    
    if (g_input->m_fCameraInThirdPerson)
    {
        // TODO: slider
        constexpr auto distance = 50.f;
        
        const auto origin = local->GetVecOrigin();
        
        Vector screen1, screen2;
        if (!g_debugoverlay->ScreenPosition(origin, screen1))
        {
            if (!g_debugoverlay->ScreenPosition(math::get_rotated_position(origin, globals.m_real_angle.y, distance), screen2))
                draw_manager::add_line(screen1.x, screen1.y, screen2.x, screen2.y, real_color);
            
            if (!g_debugoverlay->ScreenPosition(math::get_rotated_position(origin, globals.m_fake_angle.y, distance), screen2))
                draw_manager::add_line(screen1.x, screen1.y, screen2.x, screen2.y, fake_color);
            
            if (!g_debugoverlay->ScreenPosition(math::get_rotated_position(origin, globals.m_lowerbodyyaw, distance), screen2))
                draw_manager::add_line(screen1.x, screen1.y, screen2.x, screen2.y, lby_color);
        }
    }
    else
    {
        auto client_viewangles = Vector();
        auto screen_width = 0, screen_height = 0;
        
        pEngine->GetViewAngles(client_viewangles);
        pEngine->GetScreenSize(screen_width, screen_height);
        
        // TODO: slider
        constexpr auto radius = 80.f;
        
        const auto screen_center = Vector2D(screen_width / 2.f, screen_height / 2.f);
        const auto real_rot = degrees_to_radians(client_viewangles.y - pGlobals->m_real_angle.y - 90);
        const auto fake_rot = degrees_to_radians(client_viewangles.y - globals.m_fake_angle.y - 90);
        const auto lby_rot = degrees_to_radians(client_viewangles.y - globals.m_lowerbodyyaw - 90);
        
        auto draw_arrow = [&](float rot, Color color) -> void
        {
            draw_manager::add_triangle_filled(
                                              Vector2D(screen_center.x + cosf(rot) * radius, screen_center.y + sinf(rot) * radius),
                                              Vector2D(screen_center.x + cosf(rot + degrees_to_radians(10)) * (radius - 25.f),
                                                       screen_center.y + sinf(rot + degrees_to_radians(10)) * (radius - 25.f)),
                                              Vector2D(screen_center.x + cosf(rot - degrees_to_radians(10)) * (radius - 25.f),
                                                       screen_center.y + sinf(rot - degrees_to_radians(10)) * (radius - 25.f)),
                                              color);
        };
        
        draw_arrow(real_rot, real_color);
        draw_arrow(fake_rot, fake_color);
        draw_arrow(lby_rot, lby_color);
    }
}*/

void NightMode()
{
    bool done = false;
    if(vars.visuals.nightmode)
    {
        if(!done){
        }
    }
}

C_BaseCombatWeapon* getWeapon(C_BaseEntity* local) {
    auto hWeapon = local->GetActiveWeapon();
    if (!hWeapon)
        return;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(hWeapon);
}

void DrawDroppedWeapons(C_BaseCombatWeapon* weapon) {
    
    Vector vOrig = weapon->GetVecOrigin();
    int owner = weapon->GetOwner();
    
    if (owner > -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
        return;
    
    string model = GetWeaponName(weapon);
    
    boxstruct wBox;
    
    if(DrawPlayerBox(weapon, wBox)) {
        draw->drawstring(wBox.x + wBox.w / 2, wBox.y, Color::Avoz(), eFont, model.c_str(), true);
    }
}

void grenadeESP(C_BaseEntity* entity){
    
    if(!vars.visuals.grenade)
        return;
    
    if(!strstr(entity->GetClientClass()->m_pNetworkName, "Projectile"))
        return;
    
    const model_t* model = entity->GetModel();
    
    if(!model)
        return;
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(model);
    
    if(!hdr || (!strstr(hdr->name, "thrown") && !strstr(hdr->name, "dropped")))
        return;
    
    Color color;
    char* name = nullptr;
    
    IMaterial* mats[32];
    pModelInfo->GetModelMaterials(model, hdr->numtextures, mats);
    for(int i = 0; i < hdr->numtextures; i++){
        IMaterial* mat = mats[i];
        
        if(!mat)
            continue;
        
        if(strstr(mat->GetName(), "flashbang")){
            color = Color(255, 235, 59, 255);
            name = "Flashbang";
            break;
        }
        if(strstr(mat->GetName(), "smoke")){
            color = Color(97, 97, 97, 255);
            name = "Smoke";
            break;
        }
        if(strstr(mat->GetName(), "decoy")){
            color = Color(97, 97, 97, 255);
            name = "Decoy";
            break;
        }
        if(strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade")){
            color = Color(244, 67, 54, 255);
            name = "HE Grenade";
            break;
        }
        if(strstr(mat->GetName(), "incendiary")){
            color = Color(244, 67, 54, 255);
            name = "Incendiary";
            break;
        }
        if(strstr(mat->GetName(), "molotov")){
            color = Color(244, 67, 54, 255);
            name = "Molotov";
        }
    }
    
    boxstruct nBox;
    
    if(DrawPlayerBox(entity, nBox)){
        draw->drawstring(nBox.x + nBox.w + 3, nBox.y - (nBox.h/2), Color::Yellow(), eFont, name);
        box3d(entity, color);
    }
    
    
}



void DrawBombPlanted(C_BaseEntity* local, C_BasePlantedC4* bomb)
{
    if(!bomb->IsBombTicking())
        return;
    
    boxstruct Box;
    
    if(!DrawPlayerBox(bomb, Box))
        return;
    
    float flBlow    = bomb->GetBombTime();
    float bombTimer = flBlow - (pGlobals->interval_per_tick * local->GetTickBase());
    
    char buffer[128];
    
    if((local->HasDefuser() && flBlow < 5.25f) || (!local->HasDefuser() && flBlow < 10.25f))
        sprintf(buffer, "No time %.f", bombTimer);
    
    if((local->HasDefuser() && flBlow > 5.25f) || (!local->HasDefuser() && flBlow > 10.25f))
        sprintf(buffer, "Bomb %.f", bombTimer);
    
    if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f)
        sprintf(buffer, "Bomb");
    
    draw->drawstring(Box.x, Box.y, Color::Avoz(), eFont, buffer);
    
}

void DrawOtherESP() {
    // WIP
    if(!vars.visuals.enabled)
        return;
    
    if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        return;
    
    int getscreenw, getscreenh;
    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    C_BaseEntity* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        // Hitmarker
        //aw_hitmarker->paint();
        //if(pEngine->IsConnected() ** pEngine->IsInGame())
        //    hitmar
        
        
        int classID = entity->GetClientClass()->m_ClassID;
        C_BaseCombatWeapon* weapon = (C_BaseCombatWeapon*)entity;
        C_BasePlantedC4* pC4 = (C_BasePlantedC4*)entity;
        
        
        if(!weapon || !pC4)
            continue;
        
        // Draw planted bomb
        if(vars.visuals.bombtimer && classID == CPlantedC4)
            DrawBombPlanted(local, pC4);
        
        if (vars.visuals.grenade)
            grenadeESP(entity);
        
        // Manual AA prediction
        /*if(vars.visuals.manualaa)
        {
            manualaa();
        }*/
        
    }
}

void DrawPlayerESP()
{
    if(!vars.visuals.enabled)
        return;
    
    if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        return;
    
    int getscreenw, getscreenh;
    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        if(vars.visuals.enemyonly && entity->GetTeam() == local->GetTeam())
            continue;
        
        player_info_t info;
        
        pEngine->GetPlayerInfo(i, &info);
        
        auto vis = IsVisible(local, entity);
        
        Color playercolor = [&]() -> Color
        {
            if(entity->GetTeam() == 3)
                return vis ? GetColorBase(vars.colors.ctbox) : GetColorBase(vars.colors.ctbox_ign);
            else if(entity->GetTeam() == 2)
                return vis ? GetColorBase(vars.colors.tbox) : GetColorBase(vars.colors.tbox_ign);
        }();
        
        boxstruct players;
        char getYaw[255], getPitch[255];
        
        Vector vFrom = GetHitboxPosition(entity, (int)HITBOX_HEAD);
        Vector vW2s;
        Vector vvvv;
        Vector origin = entity->GetVecOrigin();
        
        if(DrawPlayerBox(entity, players)) {
        
            /* Draw box */
            if(vars.visuals.box)
                draw->drawboxoutline(players.x, players.y, players.w, players.h, playercolor);
            
            /* Draw name */
            if(vars.visuals.name)
                draw->drawstring(players.x + players.w / 2, players.y - 12, Color::White(), eFont, info.name, true);
            
            /* Draw health as text */
            if(vars.visuals.healthtext)
                draw->drawstring(players.x + players.w / 2, players.y + players.h + 8, Color::White(), eFont, std::to_string(entity->GetHealth()).c_str(), true);
            
            /* Draw health bar */
            if(vars.visuals.health)
                DrawHealthbar(players.x - 5, players.y, 3, players.h, entity->GetHealth(), Color::Green());
            
            /* Draw amour bar */
            if(vars.visuals.armour)
                DrawHealthbar(players.x, players.y + players.h + 3, players.w, 2, entity->GetArmor(), Color(72, 136, 189, 255));
            
            if(vars.visuals.active) {
                string active = GetWeaponName(getWeapon(entity));
                draw->drawstring(players.x + players.w + 3, players.y + 1, Color::White(), eFont, active.c_str());
                
            }
            
            /* Draw snaplines */
            if(vars.visuals.snapline)
                draw->drawline(getscreenw / 2, getscreenh / 2, players.x + players.w / 2, players.y + players.h, Color::White());
            
            /* Draw skeleton */
            if(vars.visuals.skeleton)
                DrawSkeleton(entity, Color::White());
            
            if(entity->IsDefusing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), eFont, "DEFUSING", true);
            
            if(entity->IsGrabbingHostage())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), eFont, "RESCUING", true);
            
            if(entity->IsRescuing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), eFont, "CARRYING", true);
            
            if((entity->IsScoped()))
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), eFont, "SCOPED", true);
            
            if((entity->GetFlashDuration() - pGlobals->curtime > 2.0f))
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Yellow(), eFont, "Flashed");
            
            draw->drawstring(players.x + players.w, players.y + 12, Color::White(), eFont, getYaw);
            draw->drawstring(players.x + players.w, players.y + 25, Color::White(), eFont, getPitch);
            
            
        }
        
    }
    
}


/* Display menu */
void pwnmymenu()
{
    
    if(pInputSystem->IsButtonDown(KEY_INSERT))
    {
        vars.menu = !vars.menu;
    }
    
}

