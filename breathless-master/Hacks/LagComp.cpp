/*#include "LagComp.h"

CBacktrack*   backtracking = new CBacktrack();
backtrackData backtrackInfo[64][MAX_TICKS];

#define TIME_TO_TICKS( dt )        ( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
backtrackData headPositions[64][16];

inline Vector btAngleVector(Vector meme)
{
    auto sy = sin(meme.y / 180.f * static_cast<float>(M_PI));
    auto cy = cos(meme.y / 180.f * static_cast<float>(M_PI));
    
    auto sp = sin(meme.x / 180.f * static_cast<float>(M_PI));
    auto cp = cos(meme.x / 180.f* static_cast<float>(M_PI));
    
    return Vector(cp * cy, cp * sy, -sp);
}

inline float distanceToPoint(Vector point, Vector lineOrigin, Vector dir)
{
    Vector pointDir = point - lineOrigin;
    
    float tempOffset = pointDir.Dot(dir) / (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (tempOffset < 0.000001f)
        return MAXFLOAT;
    
    Vector perpendicularPoint = lineOrigin + (dir * tempOffset);
    
    return (point - perpendicularPoint).Length();
}

void CBacktrack::Store(C_BaseEntity* ent)
{
    if(!ent)
        return;
    
    // add set.command_number to vars
    int arrPos = cmd->command_number % (MAX_TICKS + 1);
    
    backtrackData data;
    data.tick           = pGlobals->tickcount;
    data.vecOrigin      = ent->GetVecOrigin();
    data.headPosition   = GetHitboxPosition(ent, 0);
    data.simulationTime = ent->GetSimulationTime();
    
    backtrackInfo[ent->GetIndex()][arrPos] = data;
}

void CBacktrack::Start(C_BaseEntity* local, CUserCmd* cmd)
{
    if(!vars.aimbot.backtrack)
        return;
    
    if (!local->GetAlive())
        return;
    
    if(!cmd || !local)
        return;
    
    int bestIndex = -1;
    float bestFov = MAXFLOAT;
    
    for (int i = 0; i < 64; i++)
    {
        C_BaseEntity* entity = (C_BaseEntity*)pEntList->GetClientEntity(i);
        
        if(!entity || !local)
            continue;
        
        if(entity == local)
            continue;
        
        //if(!entity->IsPlayer())
        //    continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(!entity->GetAlive())
            continue;
        
        
        Vector headPos    = GetHitboxPosition(entity, 0);
        Vector ViewDir    = btAngleVector(cmd->viewangles + (local->GetPunchAngles() * 2.f));
        float FOVDistance = distanceToPoint(headPos, local->GetEyePosition(), ViewDir);
        
        if (bestFov > FOVDistance)
        {
            bestFov = FOVDistance;
            bestIndex = i;
        }
    }
    
    if(bestIndex == -1)
        return;
    
    float bestSimTime   = 0.0;
    float tempFloat     = MAXFLOAT;
    Vector ViewDir      = btAngleVector(cmd->viewangles + (local->GetPunchAngles() * 2.f));
    
    for (int t = 0; t < MAX_TICKS; ++t)
    {
        Vector headScreen;
        if(!WorldToScreen(backtrackInfo[bestIndex][t].headPosition, headScreen))
            continue;
        
        float tempFOVDistance = distanceToPoint(backtrackInfo[bestIndex][t].headPosition, local->GetEyePosition(), ViewDir);
        
        if (tempFOVDistance > tempFloat && backtrackInfo[bestIndex][t].simulationTime > local->GetSimulationTime() - 1)
        {
            tempFloat    = tempFOVDistance;
            bestSimTime  = backtrackInfo[bestIndex][t].simulationTime;
        }
    }
    
    if (cmd->buttons & IN_ATTACK)
    {
        cmd->tick_count = TIME_TO_TICKS(bestSimTime);
    }
}*/


/*#include "LagComp.h"
#define TIME_TO_TICKS( dt )        ( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

void BackTrack::Update(int tick_count)
{
    if (!vars.misc.fakelag)
        return;

    latest_tick = tick_count;
    for (int i = 0; i < 64; i++)
    {
        UpdateRecord(i);
    }
}

bool BackTrack::IsTickValid(int tick)
{
    int delta = latest_tick - tick;
    float deltaTime = delta * pGlobals->interval_per_tick;
    return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
    C_BaseEntity* pEntity = pEntList->GetClientEntity(i);
    if (pEntity && pEntity->GetAlive() && !pEntity->GetDormant())
    {
        float lby = pEntity->GetLowerBodyYawTarget();
        if (lby != records[i].lby)
        {
            records[i].tick_count = latest_tick;
            records[i].lby = lby;
            records[i].headPosition = GetHitboxPosition(pEntity, 0);
        }
    }
    else
    {
        records[i].tick_count = 0;
    }
}

bool BackTrack::RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint)
{
    if (IsTickValid(records[i].tick_count))
    {
        aimPoint = records[i].headPosition;
        cmd->tick_count = records[i].tick_count;
        return true;
    }
    return false;
}

void BackTrack::legitBackTrack(CUserCmd* cmd, C_BaseEntity* pLocal)
{
    if (vars.aimbot.backtrack)
    {
        int bestTargetIndex = -1;
        float bestFov = FLT_MAX;
        player_info_t info;
        if (!pLocal->GetAlive())
            return;

        for (int i = 0; i < pEngine->GetMaxClients(); i++)
        {
            auto entity = (C_BaseEntity*)pEntList->GetClientEntity(i);

            if (!entity || !pLocal)
                continue;

            if (entity == pLocal)
                continue;

            pEngine->GetPlayerInfo(i, &info);

            if (entity->GetDormant())
                continue;

            if (entity->GetTeam() == pLocal->GetTeam())
                continue;

            if (entity->GetAlive())
            {
				
                float simtime = entity->GetSimulationTime();
                Vector hitboxPos = GetHitboxPosition(entity, 0);

                headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
                Vector ViewDir = cmd->viewangles + (pLocal->GetPunchAngles() * 2.f);
                float FOVDistance = distance_point_to_line(hitboxPos, pLocal->GetEyePosition(), ViewDir);

                if (bestFov > FOVDistance)
                {
                    bestFov = FOVDistance;
                    bestTargetIndex = i;
                }
            }
        }

        float bestTargetSimTime;
        if (bestTargetIndex != -1)
        {
            float tempFloat = FLT_MAX;
            Vector ViewDir = cmd->viewangles + (pLocal->GetPunchAngles() * 2.f);
            for (int t = 0; t < 12; ++t)
            {
                float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
                if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
                {
                    tempFloat = tempFOVDistance;
                    bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
                }
            }
            if (cmd->buttons & IN_ATTACK)
            {
                //cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
            }
        }
    }
}

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][12];
*/
