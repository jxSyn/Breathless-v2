//
//  hitmarker.hpp
//  vHook
//
//  Pasted by Bellez on 21/5/18. (UK Date)
//  Copyright © 2018 Justin. All rights reserved.
// Pro Hacker Tut
// Aimware Hitmarkers
//

#pragma once

#include "../main.h"

struct impact_info {
    float x,y, z;
    long long time;
};

struct hitmarker_info{
    impact_info impact;
    int alpha;
};

class Hitmarker: IGameEventListener2 {
public:
    void initilisze();
    void paint();
private:
    void FireGameEvent(IGameEvent* event) ;
    int GameEventDebugID(void);
    void player_hurt(IGameEvent* event) ;
    void bullet_impact(IGameEvent* event) ;
    C_BaseEntity* get_player(int userid);
    std::vector<impact_info> impact;
    std::vector<hitmarker_info> hitmarkers;
};

extern Hitmarker* aw_hitmarker;

/*
namespace Hitmarkers {
    void FireGameEvent(IGameEvent* event);
    void Paint();
}*/
