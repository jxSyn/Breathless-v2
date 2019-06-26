/*]#include "antiaiminfos.h"


QAngle fakeAngle = {0, 0, 0};
QAngle realAngle = {0, 0 ,0};
float lbyAngle = 0;


void AntiAimInfo(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket)
{
	if (!vars.visuals.antiaiminfos|| !pEngine->IsInGame())
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localPlayer || !localPlayer->GetAlive())
		return;
     
	char* fakeAngleBuf;
	char* realAngleBuf;
	char* lbyAngleBuf;
    
    asprintf(&realAngleBuf, ("Real: %.3f"), local->GetYawRotation());
    asprintf(&fakeAngleBuf, ("Fake: %.3f") , local->GetHeadRotation());
    asprintf(&lbyAngleBuf, ("LBY: %.3f"), lbyAngle);

    draw->drawstring(50, 985, realAngleBuf, eFont, Color::Green()); // Real Angle
    draw->drawstring(50, 1000, fakeAngleBuf, eFont, Color::Red());  // Fake Angle
    draw->drawstring(50, 1015, lbyAngleBuf, eFont, Color::Blue());  // Lower Body Angle

	free(fakeAngleBuf);
	free(realAngleBuf);
	free(lbyAngleBuf);
    
    if (bSendPacket)
        fakeAngle = cmd->viewangles;
    else
        realAngle = cmd->viewangles;
    
    lbyAngle = local->GetLowerBodyYawTarget();

}

void AntiAimInfos(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket)
{
	if (!vars.visuals.antiaiminfos || !pEngine->IsInGame())
		return;

	C_BasePlayer* localPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localPlayer || !localPlayer->GetAlive())
		return;

	if (bSendPacket)
        fakeAngle = cmd->viewangles;
    else
        realAngle = cmd->viewangles;

	lbyAngle = local->GetLowerBodyYawTarget();

	
}*/

