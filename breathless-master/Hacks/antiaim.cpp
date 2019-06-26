//
//  antiaim.cpp
//  vHook
//

//#include "hacks.h"
#include "antiaim.h"
#include "../Hacks/autowall.h"
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)

//#include "../Hooks/FrameStage.h"

Vector atTargets;
bool isManual = false;

float next_lby_update;
float old_lby;
bool Swtich = false;

float GetLatency(INetChannelInfo* nci)
{
    // INetChannelInfo *nci = Interfaces::Engine->GetNetChannelInfo();
    if (nci)
    {
        
        float Latency = nci->GetAvgLatency(FLOW_OUTGOING) + nci->GetAvgLatency(FLOW_INCOMING);
        return Latency;
    }
    else
    {
        
        return 0.0f;
    }
}
float GetOutgoingLatency(INetChannelInfo* nci)
{
    // INetChannelInfo *nci = Interfaces::Engine->GetNetChannelInfo();
    if (nci)
    {
        
        float OutgoingLatency = nci->GetAvgLatency(FLOW_OUTGOING);
        return OutgoingLatency;
    }
    else
    {
        
        return 0.0f;
    }
}
int jitterRange = 0;
float GetIncomingLatency(INetChannelInfo* nci)
{
    // INetChannelInfo *nci = pEngine->GetNetChannelInfo();
    if (nci)
    {
        float IncomingLatency = nci->GetAvgLatency(FLOW_INCOMING);
        return IncomingLatency;
    }
    else
    {
        
        return 0.0f;
    }
}

float OldLBY;
float LBYBreakerTimer;
float LastLBYUpdateTime;
bool bSwitch;

float CurrentVelocity(C_BaseEntity* local)
{
    int vel = local->GetVelocity().Length2D();
    return vel;
}
bool NextLBYUpdate(C_BaseEntity* local)
{
    //  IClientEntity* LocalPlayer = hackManager.pLocal();
    
    float flServerTime = (float)(local->GetTickBase()  * pGlobals->interval_per_tick);
    
    
    if (OldLBY != local->GetLowerBodyYawTarget())
    {
        
        LBYBreakerTimer++;
        OldLBY = local->GetLowerBodyYawTarget();
        bSwitch = !bSwitch;
        LastLBYUpdateTime = flServerTime;
    }
    
    if (CurrentVelocity(local) > 1)
    {
        LastLBYUpdateTime = flServerTime;
        return false;
    }
    
    if ((LastLBYUpdateTime + 1 - (GetLatency(nci) * 2) < flServerTime) && (local->GetFlags() & FL_ONGROUND))
    {
        if (LastLBYUpdateTime + 1.099 - (GetLatency(nci) * 2) < flServerTime)
        {
            LastLBYUpdateTime += 1.099;
        }
        return true;
    }
    return false;
}

bool NextMovingLBYUpdate(C_BaseEntity* local)
{
    //  IClientEntity* LocalPlayer = hackManager.pLocal();
    
    float flServerTime = (float)(local->GetTickBase()  * pGlobals->interval_per_tick);
    
    
    if (OldLBY != local->GetLowerBodyYawTarget())
    {
        
        LBYBreakerTimer++;
        OldLBY = local->GetLowerBodyYawTarget();
        bSwitch = !bSwitch;
        LastLBYUpdateTime = flServerTime;
    }
    
    if (CurrentVelocity(local) > 1)
    {
        LastLBYUpdateTime = flServerTime;
        return false;
    }
    
    if ((LastLBYUpdateTime + 1 - (GetLatency(nci) * 2) < flServerTime) && (local->GetFlags() & FL_ONGROUND))
    {
        if (LastLBYUpdateTime + 0.22 - (GetLatency(nci) * 2) < flServerTime)
        {
            LastLBYUpdateTime += 0.22;
        }
        return true;
    }
    return false;
}

float WallThickness(Vector from, Vector to, C_BasePlayer* skip, C_BasePlayer* skip2)
{
    Vector endpos1, endpos2;
    
    Ray_t ray;
    ray.Init(from, to);
    
    CTraceFilterSkipTwoEntities filter(skip, skip2);
    
    trace_t trace1, trace2;
    pEngineTrace->TraceRay(ray, MASK_SHOT_BRUSHONLY, &filter, &trace1);
    
    if (trace1.DidHit())
        endpos1 = trace1.endpos;
    else
        return -1.f;
    
    ray.Init(to, from);
    pEngineTrace->TraceRay(ray, MASK_SHOT_BRUSHONLY, &filter, &trace2);
    
    if (trace2.DidHit())
        endpos2 = trace2.endpos;
    
    return endpos1.DistTo(endpos2);
}


/*void freestanding(CUserCmd* cmd)
 {
 static float FinalAngle;
 bool bside1 = false;
 bool bside2 = false;
 bool autowalld = false;
 
 C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
 
 for (int i = 0; i <= pEngine->GetMaxClients(); ++i)
 {
 C_BaseEntity* pPlayerEntity = pEntList->GetClientEntity(i);
 
 if (!pPlayerEntity
 || !pPlayerEntity->GetAlive()
 || pPlayerEntity->GetDormant()
 || pPlayerEntity == localplayer
 || pPlayerEntity->GetTeam() == localplayer->GetTeam())
 continue;
 
 float angToLocal = CalcAngle(localplayer->GetVecOrigin(), pPlayerEntity->GetVecOrigin()).y;
 Vector ViewPoint = pPlayerEntity->GetVecOrigin() + Vector(0, 0, 90);
 
 Vector2D Side1 = { (45 * sin(GRD_TO_BOG(angToLocal))),(45 * cos(GRD_TO_BOG(angToLocal))) };
 Vector2D Side2 = { (45 * sin(GRD_TO_BOG(angToLocal + 180))) ,(45 * cos(GRD_TO_BOG(angToLocal + 180))) };
 
 Vector2D Side3 = { (50 * sin(GRD_TO_BOG(angToLocal))),(50 * cos(GRD_TO_BOG(angToLocal))) };
 Vector2D Side4 = { (50 * sin(GRD_TO_BOG(angToLocal + 180))) ,(50 * cos(GRD_TO_BOG(angToLocal + 180))) };
 
 Vector Origin = localplayer->GetVecOrigin();
 
 Vector2D OriginLeftRight[] = { Vector2D(Side1.x, Side1.y), Vector2D(Side2.x, Side2.y) };
 
 Vector2D OriginLeftRightLocal[] = { Vector2D(Side3.x, Side3.y), Vector2D(Side4.x, Side4.y) };
 
 for (int side = 0; side < 2; side++)
 {
 Vector OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 80 };
 Vector OriginAutowall2 = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };
 
 if (Autowall::CanHitFloatingPoint(OriginAutowall, ViewPoint))
 {
 if (side == 0)
 {
 bside1 = true;
 FinalAngle = angToLocal + 90;
 }
 else if (side == 1)
 {
 bside2 = true;
 FinalAngle = angToLocal - 90;
 }
 autowalld = true;
 }
 else
 {
 for (int side222 = 0; side222 < 2; side222++)
 {
 Vector OriginAutowall222 = { Origin.x + OriginLeftRight[side222].x,  Origin.y - OriginLeftRight[side222].y , Origin.z + 80 };
 
 if (Autowall::CanHitFloatingPoint(OriginAutowall222, OriginAutowall2))
 {
 if (side222 == 0)
 {
 bside1 = true;
 FinalAngle = angToLocal + 90;
 }
 else if (side222 == 1)
 {
 bside2 = true;
 FinalAngle = angToLocal - 90;
 }
 autowalld = true;
 }
 }
 }
 }
 }
 
 if (!autowalld || (bside1 && bside2)) {
 cmd->viewangles.y += 180;
 }
 else
 cmd->viewangles.y = FinalAngle;
 
 if (vars.aimbot.jitter != 0)
 {
 float Offset = vars.aimbot.jitter;
 
 
 Swtich ? cmd->viewangles.y -= Offset : cmd->viewangles.y += Offset;
 }
 }*/

float fov_player(Vector ViewOffSet, Vector View, C_BaseEntity* entity, int hitbox)
{
    // Anything past 180 degrees is just going to wrap around
    const float MaxDegrees = 180.0f;
    
    // Get local angles
    Vector Angles = View;
    
    // Get local view / eye position
    Vector Origin = ViewOffSet;
    
    // Create and intiialize vectors for calculations below
    Vector Delta(0, 0, 0);
    //Vector Origin(0, 0, 0);
    Vector Forward(0, 0, 0);
    
    // Convert angles to normalized directional forward vector
    AngleVectors(Angles, &Forward);
    
    Vector AimPos = GetHitboxPosition(entity, hitbox); //pvs fix disabled
    
    VectorSubtract(AimPos, Origin, Delta);
    //Delta = AimPos - Origin;
    
    // Normalize our delta vector
    NormalizeNum(Delta, Delta);
    
    // Get dot product between delta position and directional forward vectors
    float DotProduct = Forward.Dot(Delta);
    
    // Time to calculate the field of view
    return (acos(DotProduct) * (MaxDegrees / M_PI));
}
/*
 float Vector::DistTo(const Vector &vOther) const
 {
 Vector delta;
 
 delta.x = x - vOther.x;
 delta.y = y - vOther.y;
 delta.z = z - vOther.z;
 
 return delta.Length();
 }
 */
int closest_to_crosshair()
{
    int index = -1;
    float lowest_fov = INT_MAX;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    
    if (!local)
        return -1;
    
    Vector local_position = local->GetVecOrigin() + local->GetVecViewOffset();
    
    Vector angles;
    pEngine->GetViewAngles(angles);
    
    for (int i = 1; i <= pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if (!entity || !entity->GetAlive() || entity->GetTeam() == local->GetTeam() || entity->GetDormant() || entity == local)
            continue;
        
        float fov = fov_player(local_position, angles, entity, 0);
        
        if (fov < lowest_fov)
        {
            lowest_fov = fov;
            index = i;
        }
    }
    
    return index;
}
////////////////////////////////////////////////////***/////////////////////////////////////////////////////////////
void AngleVectors3(const Vector &angles, Vector& forward, Vector& right, Vector& up)
{
    float sr, sp, sy, cr, cp, cy;
    
    SinCos(DEG2RAD(angles[1]), &sy, &cy);
    SinCos(DEG2RAD(angles[0]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);
    
    forward.x = (cp * cy);
    forward.y = (cp * sy);
    forward.z = (-sp);
    right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
    right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
    right.z = (-1 * sr * cp);
    up.x = (cr * sp * cy + -sr * -sy);
    up.y = (cr * sp * sy + -sr * cy);
    up.z = (cr * cp);
}

inline float NormalizeYaw(float yaw)
{
    if (yaw > 180)
        yaw -= (round(yaw / 360) * 360.f);
    else if (yaw < -180)
        yaw += (round(yaw / 360) * -360.f);
    
    return yaw;
}

//--------------------------------------------------------------------------------

float Freestand(C_BaseEntity* local, CUserCmd* cmd)
{
    //Vector oldAngle = cmd->viewangles;
    bool flip = false;
    float Back, Right, Left;
    bool no_active = true;
    Vector src3D, dst3D, forward, right, up, src, dst;
    trace_t tr;
    Ray_t backray, rightray, leftray;
    CTraceFilter filter;
    
    Vector angles;
    pEngine->GetViewAngles(angles);
    
    AngleVectors3(angles, forward, right, up);
    
    filter.pSkip = local;
    src3D = local->GetVecOrigin() + local->GetVecViewOffset();
    dst3D = src3D + (forward * 384.f);
    
    backray.Init(src3D, dst3D);
    pEngineTrace->TraceRay(backray, MASK_SHOT, &filter, &tr);
    Back = (tr.endpos - tr.startpos).Length();
    
    rightray.Init(src3D + right * 35.f, dst3D + right * 35.f);
    pEngineTrace->TraceRay(rightray, MASK_SHOT, &filter, &tr);
    Right = (tr.endpos - tr.startpos).Length();
    
    leftray.Init(src3D - right * 35.f, dst3D - right * 35.f);
    pEngineTrace->TraceRay(leftray, MASK_SHOT, &filter, &tr);
    Left = (tr.endpos - tr.startpos).Length();
    
    if (Left > Right){
        
        if (flip)
        {
            cmd->viewangles.y -= 90.f - RandomFloat(5, vars.aimbot.jitter);
        }
        else
        {
            cmd->viewangles.y -= 90 + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }else if (Right > Left){
        
        if (flip)
        {
            cmd->viewangles.y += 90.f - RandomFloat(5, vars.aimbot.jitter);
        }
        else
        {
            cmd->viewangles.y += 90 + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }else if (Back > Right || Back > Left){
        
        if (flip)
        {
            cmd->viewangles.y = 180.f - RandomFloat(5, vars.aimbot.jitter);
        }
        else
        {
            cmd->viewangles.y = 180 + RandomFloat(5, vars.aimbot.jitter);
        }
        
    } else if(no_active){
        
        if (flip)
        {
            cmd->viewangles.y += 180.f - RandomFloat(5, vars.aimbot.jitter);
        }
        else
        {
            cmd->viewangles.y += 180 + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    flip = !flip;
    return 0;
}

void manualAAIndicators(){
    {
        if ( !vars.visuals.enabled )
            return;
        if ( !vars.misc.antiaim )
            return;
        
        static bool left = false;
        static bool right = false;
        static bool back = false;
        
        
        int Height, Width;
        pEngine->GetScreenSize(Height, Width);
        
        int x = Width / 2;
        int y = Height / 2;
        
        if (pInputSystem->IsButtonDown(KEY_LEFT)) {
            left = true; right = false; back = false;
        }
        else if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
            left = false; right = true; back = false;
        }
        else if (pInputSystem->IsButtonDown(KEY_DOWN)) {
            left = false; right = false; back = true;
        }
        
        
        
        
        if(isManual){
            
            
            if( right ) {
                draw->drawstring(y + 40, x, vars.colors.menu, lbyfont, (">")); // Green
                draw->drawstring(y - 60, x, Color(255, 255, 255, 255), lbyfont, ("<")); // White
                draw->drawstring(y - 5, x + 50, Color(255, 255, 255, 255), lbyfont, ("V")); // White
            }
            
            if( left ){
                draw->drawstring(y + 40, x, Color(255, 255, 255, 255), lbyfont, (">")); // White
                draw->drawstring(y - 60, x, vars.colors.menu, lbyfont, ("<")); // Green
                draw->drawstring(y - 5, x + 50, Color(255, 255, 255, 255), lbyfont, ("V")); // White
            }
            
            if( back ){
                draw->drawstring(y + 40, x, Color(255, 255, 255, 255), lbyfont, (">")); // White
                draw->drawstring(y - 60, x, Color(255, 255, 255, 255), lbyfont, ("<")); // White
                draw->drawstring(y - 5, x + 50, vars.colors.menu, lbyfont, ("V")); // Green
            }
            
            
            
        }
    }
}

void doManual(CUserCmd* cmd){
    static bool left = false;
    static bool right = false;
    static bool back = false;
    
    bool flip = false;
    
    int Height, Width;
    pEngine->GetScreenSize(Height, Width);
    
    int x = Width / 2;
    int y = Height / 2;
    
    if (pInputSystem->IsButtonDown(KEY_LEFT)) {
        left = true; right = false; back = false;
    }
    else if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
        left = false; right = true; back = false;
    }
    else if (pInputSystem->IsButtonDown(KEY_DOWN)) {
        left = false; right = false; back = true;
    }
    if ( left ){
        
        if (flip)
        {
            cmd->viewangles.y += 90.f - RandomFloat(5, vars.aimbot.jitter);
        }else
        {
            cmd->viewangles.y += 90 + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    
    if ( right ){
        
        if (flip)
        {
            cmd->viewangles.y -= 90.f + RandomFloat(5, vars.aimbot.jitter);
        }else
        {
            cmd->viewangles.y -= 90 - RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    if ( back ){
        
        if (flip)
        {
            cmd->viewangles.y += 180.f - RandomFloat(5, vars.aimbot.jitter);
        }else
        {
            cmd->viewangles.y += 180.f + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    flip = !flip;
    
}

void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon)
{
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (!weapon)
        return;
    
    if (weapon->IsGrenade())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
        return;
    
    if (local->GetImmune())
        return;
    
    /* if(NextLBYUpdate(cmd)){
     cmd->viewangles.y += vars.misc.delta;
     } */
    
    
    if (!vars.misc.fakelag)
        *bSendPacket = cmd->command_number % 2;
    
    if(vars.misc.pitch)
    {
        cmd->viewangles.x = 89;
    }
    
    if(vars.misc.AAenabled)
    {
        
        if(!vars.misc.freestand){
            doManual(cmd);
            isManual = true;
        }
        else{
            Freestand(local, cmd);
            isManual = false;
        }
    }
    cmd->viewangles.ClampAngles();
}
