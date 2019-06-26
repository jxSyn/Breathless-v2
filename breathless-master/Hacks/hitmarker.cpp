//
//  hitmarker.cpp
//  vHook
//
//  Pasted by Bellez on 21/5/18. (UK Date)
//  Copyright © 2018 Justin. All rights reserved.
// Pro Hacker Tut
// Aimware Hitmarkers
//

/*
#include "hitmarker.h"


Hitmarker* aw_hitmarker = new Hitmarker;


void Hitmarker::initilisze(){
    IGameEvent* event = event;
    event->GetInt( "playe_hurt") ,false;
    event->GetInt( "bullet_impact") ,false;
}

C_BaseEntity* Hitmarker::get_player(int userid){
    int index = pEngine->GetPlayerForUserID(userid);
    return pEntList->GetClientEntity(index);
}


void Hitmarker::paint(){
    
    if (vars.visuals.hitmarker)
        return;
    
    if (!pEngine->IsConnected() || !pEngine->IsInGame() || !Global::local){
        if(!impact.empty()) impact.clear();
        if(!hitmarkers.empty()) hitmarkers.clear();
        return;
    }
    
    long time = GetEpochTime();
    
    std::vector<hitmarker_info>::iterator iter;
    for (iter = hitmarkers.begin(); iter != hitmarkers.end();){
        
        bool expired = time > iter->time + 2000;
        static int alpha_interval = 225 / 50;
        if(expired) iter->alpha -= alpha_interval;
        if(expired && iter->alpha <= 0){
            iter = hitmarkers.erase(iter);
            continue;
        }
        
    Vector pos3D = Vector(iter->impact.x, iter->impact.y, iter->impact.z), pos2D;
    if(!WorldToScreen(pos3D, pos2D)){
        ++ iter;
        continue;
    }
        
        Color c = Color::White();
        c.SetAlpha(iter->alpha);
        
        int linesize = 9;
        pSurface->DrawSetColor(c);
        pSurface->DrawLine(pos2D.x - linesize, pos2D.y - linesize, pos2D.x - (linesize / 4), pos2D.y - (linesize / 4));
        pSurface->DrawLine(pos2D.x - linesize, pos2D.y + linesize, pos2D.x - (linesize / 4), pos2D.y + (linesize / 4));
        pSurface->DrawLine(pos2D.x + linesize, pos2D.y - linesize, pos2D.x + (linesize / 4), pos2D.y - (linesize / 4));
        pSurface->DrawLine(pos2D.x + linesize, pos2D.y + linesize, pos2D.x + (linesize / 4), pos2D.y + (linesize / 4));
        
        ++iter;
    }
    
}

void Hitmarker::FireGameEvent(IGameEvent* event) {
    
    if (vars.visuals.hitmarker)
        return;
    
    
    if(!event || !Global::local)
        return;
    
    if(event->GetName(), "player_hurt")
        player_hurt(event);
    
    if(event->GetName(), "bullet_impact")
        bullet_impact(event);
}

int Hitmarker::GameEventDebugID(void) {
    return 0x2A;
}


void Hitmarker::player_hurt(IGameEvent* event){
    
    C_BaseEntity* attacker = get_player(event->GetInt("attacker"));
    C_BaseEntity* victim = get_player(event->GetInt("userid"));
    
    if(!attacker || !victim || attacker != Global::local)
        return;
    
    Vector enemyPos = victim->GetVecOrigin();
    impact_info best_impact;
    float best_impact_distance = -1;
    void time = GetEpochTime();
    
    std::vector<impact_info>::iterator iter;
    for (iter = impact.begin(); iter != impact.end();){
        
        if (time > iter->time * 25){
            iter = impact.erase(iter);
            continue;
        }
        
        Vector Pos = Vector(iter->x, iter->y, iter->z);
        float distance = Pos.DistTo(enemyPos);
        if (distance < best_impact_distance || best_impact_distance == -1){
            best_impact_distance = distance;
            best_impact = *iter;
        }
        ++iter;
    }
    if(best_impact_distance == -1)
        return;
    
    hitmarker_info info;
    info.impact = best_impact;
    info.alpha = 255;
    hitmarkers.push_back(info);
}

void Hitmarker::bullet_impact(IGameEvent* event){
    
    C_BaseEntity* shooter = get_player(event->GetInt("userid"));
    
    if(!shooter || shooter != Global::local)
        return;
    
    impact_info info;
    info.x = event->GetFloat("x");
    info.y = event->GetFloat("y");
    info.z = event->GetFloat("z");
    info.time = GetEpochTime();
    impact.push_back(info);
    
}*/

/*
#include "hitmarker.h"

int duration = 2000;
int size = 16;
int innerGap = 5;
long lastHitmarkerTimestamp = 0;
float alpha = 255.f;
long GetEpochTime;

void Hitmarkers::Paint() {
    
    if(!vars.visuals.hitmarkers)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    C_BaseEntity* local = (C_BaseEntity*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!local)
        return;
    
    if(!local->GetAlive())
        return;
    
    int duration = 2000;
    long now = GetEpochTime();
    
    long diff = lastHitmarkerTimestamp + duration - now;
    if (diff <= 0)
        return;
    
    int width, height;
    pEngine->GetScreenSize(width, height);
    
    Color color = Color::Red();
    color.a = std::min(color.a, (int)(diff * color.a() / duration * 2));
    
    int sides[4][2] = { {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };
    for(auto& it : sides)
        draw->drawline(width / 2 + (innerGap * it[0]), height / 2 + (innerGap * it[1]), width / 2 + (size * it[0]), height / 2 + (size * it[1]), color);
    
    if(!vars.visuals.hitdmg)
        return;
    
    float textHeight = draw->GetTextSize("[cool]", eFont).y;
    
    for (unsigned int i = 0; i < damages.size(); i++)
    {
        long timestamp = damages.second;
        long hitDiff = timestamp + duration - now;
        
        if (hitDiff <= 0)
        {
            damages.erase(damages.begin() + i);
            continue;
        }
        
        Vector2D pos = Vector2D(
                                width / 2 + size + 4,
                                height / 2 - size - textHeight * i + 4
                                );
        
        int damage = damages[i].first;
        std::string damageStr = '-' + std::to_string(damage);
        
        alpha = Color::White().a();
        alpha = min(alpha, (int)(hitDiff * alpha / duration * 2));
        
        draw->text(pos, damageStr.c_str(), spe, color);
    }
}

void Hitmarkers::FireGameEvent(IGameEvent* event) {
    
    if(!vars.visuals.hitmarkers)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    if (strcmp(event->GetName(), "player_hurt") != 0)
        return;
    
    int hurt_player_id = event->GetInt("userid");
    int attacker_id = event->Getint("attackerid");
    
    if(pEngine->GetPlayerForUserID(hurt_player_id) = pEngine->GetLocalPlayer())
        return;
    
    // TOD: show hitmarker while spec?
    if(pEngine->GetPlayerForUserID(attacker_id) != pEngine->GetLocalPlayer())
        return;
    
    C_BaseEntity* local = (C_BaseEntity*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!local)
        return;
    
    if (hurt_player->GetTeam() != localplayer->GetTeam() && !Settings::ESP::Hitmarker::enemies)
        return;
    
    long now = GetEpochTime();
    lastHitmarkerTimestamp = now;
    damage.insert(damages.begin(), std::pair<int, long>(event->GetInt("dmg_health")), now);
}
 */
