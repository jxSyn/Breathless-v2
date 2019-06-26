#include "main.h"

namespace Global
{
    CUserCmd*     cmd;
    C_BasePlayer* local;
    C_BaseCombatWeapon* localWeapon;
}

int __attribute__((constructor)) Init()
{
    
    InitializeInterfaces();
    
    InitializeVMTs();
    
    InitializeHooks();
    
    NetVarManager::DumpNetvars();
    
    Offsets::getOffsets();
    
    UpdateResolver();
    
    PrintInfo();
    
    return 0;
}

void __attribute__((constructor)) DeInit()
{

}
