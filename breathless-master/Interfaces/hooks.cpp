#include "main.h"
#include "skinchanger.h"

bool* bSendPacket = nullptr;

void InitializeInterfaces()
{
    pSurface        = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel          = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pEffects        = GetInterface<CEffects>("./bin/osx64/engine.dylib", "VEngineEffects"); 
    pCvar           = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient         = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client_panorama.dylib", "VClient");
    pEngine         = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList        = GetInterface<IClientEntityList>("./csgo/bin/osx64/client_panorama.dylib", "VClientEntityList");
    pOverlay        = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    pEngineTrace    = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo      = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    pInputSystem    = GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    pModelRender    = GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    pMatSystem      = GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    pPrediction     = GetInterface<IPrediction>("./csgo/bin/osx64/client_panorama.dylib", "VClientPrediction");
    pGameMovement   = GetInterface<IGameMovement>("./csgo/bin/osx64/client_panorama.dylib", "GameMovement");
    pPhysics        = GetInterface<IPhysicsSurfaceProps>("./bin/osx64/vphysics.dylib", "VPhysicsSurfaceProps");
    pGameEventManager = GetInterface<IGameEventManager2>("./bin/osx64/engine.dylib", "GAMEEVENTSMANAGER002", true);
}

void ProtectAddr(void* addr, int prot)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    void* address = (void *)((long)(uintptr_t)addr & ~(pagesize - 1));
    mprotect(address, sizeof(address), prot);
}

void InitializeVMTs()
{
    uintptr_t findClientMode = CPatternScanner::Instance()->GetPointer("client_panorama.dylib",(unsigned char*)CLIENTMODE_SIG, CLIENTMODE_MASK, 0xA) + 0x4;
    uintptr_t findGlobalVars = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)GLOBALS_SIG, GLOBALS_MASK, 0x3) + 0x4;
    uintptr_t findRankReveal = CPatternScanner::Instance()->GetPointer("client_panorama.dylib",(unsigned char*)RANKREVEAL_SIG, RANKREVEAL_MASK, 0x15) + 0x4;
    uintptr_t findClanTag    = CPatternScanner::Instance()->GetPointer("engine.dylib", (unsigned char*) CLANTAG_SIG, CLANTAG_MASK, 0xB) + 0x4;
    uintptr_t sendPacketPtr =  CPatternScanner::Instance()->GetProcedure("engine.dylib", (unsigned char*)SENDPACKET_SIG, SENDPACKET_MASK, 0x1) + 0x2;

    bSendPacket = reinterpret_cast<bool*>(sendPacketPtr);
    ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);

    void* handle = dlopen("./csgo/bin/osx64/client_panorama.dylib", RTLD_NOLOAD | RTLD_NOW);
    RandomInt       = reinterpret_cast<RandomIntFn>(dlsym(handle, "RandomInt"));
    RandomSeed      = reinterpret_cast<RandomSeedFn>(dlsym(handle, "RandomSeed"));
    dlclose(handle);
    
    SetClanTag  = reinterpret_cast<SendClanTagFn>(findClanTag);
    pClientMode = reinterpret_cast<IClientMode*>(findClientMode);
    pGlobals    = *reinterpret_cast<CGlobalVarsBase**>(findGlobalVars);
    MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(findRankReveal);

    paintVMT        = new VMT(pPanel);
    createmoveVMT   = new VMT(pClientMode);
    clientVMT       = new VMT(pClient);
    modelVMT        = new VMT(pModelRender);
    predVMT         = new VMT(pPrediction);
    game_event_vmt  = new VMT(pGameEventManager);
}

void InitializeHooks()
{
    paintVMT->HookVM((void*)hkPaintTraverse, 42);
    paintVMT->ApplyVMT();
        
    createmoveVMT->HookVM((void*)hkCreateMove, 25);
    createmoveVMT->HookVM((void*)hkOverrideView, 19);
    createmoveVMT->ApplyVMT();
    
    clientVMT->HookVM((void*)hkKeyEvent, 21);
    
    clientVMT->HookVM((void*)hkFrameStage, 37);
    clientVMT->ApplyVMT();
    
    modelVMT->HookVM((void*)hkDrawModelExecute, 21);
    modelVMT->ApplyVMT();
    
    predVMT->HookVM((void*)hkRunCommand, 20);
    predVMT->ApplyVMT();

    game_event_vmt->HookVM((void*)hkFireEventClientSide, 36);
    game_event_vmt->ApplyVMT();
    
    g_pSequence = (RecvVarProxyFn)NetVarManager::HookProp("DT_BaseViewModel", "m_nSequence", HSequenceProxyFn);
}

void Unhook()
{
    //pEngine->ExecuteClientCmd("cl_mouseenable 1");
    paintVMT        ->ReleaseVMT();
    createmoveVMT   ->ReleaseVMT();
    clientVMT       ->ReleaseVMT();
    modelVMT        ->ReleaseVMT();
    predVMT         ->ReleaseVMT();
    
    delete paintVMT;
    delete createmoveVMT;
    delete clientVMT;
    delete modelVMT;
    delete predVMT;
}

void UpdateResolver()
{
    //OldProxy_X = (RecvVarProxyFn)NetVarManager::HookProp("DT_CSPlayer", "m_angEyeAngles[0]", FixPitch);
    OldProxy_Y = (RecvVarProxyFn)NetVarManager::HookProp("DT_CSPlayer", "m_angEyeAngles[1]", FixYaw);
}

void PrintInfo()
{
    pCvar->ConsoleColorPrintf(Color::White(), "[breathless-v2] Injected successfully! ");
    
}

