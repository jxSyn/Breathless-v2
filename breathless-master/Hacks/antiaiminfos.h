#include "hooks.h"
#include "esp.h"
#include "main.h"
#include "antiaim.h"

/*
namespace AntiAimInfos
{

	// Hooks
	void PaintTraverse();
	void CreateMove(CUserCmd* cmd);
};
*/
void AntiAimInfo(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket);
