#pragma once

extern ISurface*            pSurface;
extern CEffects*            pEffects;
extern IPanel*              pPanel;
extern ICvar*               pCvar;
extern IBaseClientDLL*      pClient;
extern IClientEntityList*   pEntList;
extern IVDebugOverlay*      pOverlay;
extern IEngineClient*       pEngine;
extern IVModelInfo*         pModelInfo;
extern IEngineTrace*        pEngineTrace;
extern IClientMode*         pClientMode;
extern CGlobalVarsBase*     pGlobals;
extern IInputSystem*        pInputSystem;
extern CInput*              pInput;
extern IMaterialSystem*     pMatSystem;
extern IVModelRender*       pModelRender;
extern IPrediction*         pPrediction;
extern IGameMovement*       pGameMovement;
extern IMoveHelper*         pMoveHelper;
extern IPhysicsSurfaceProps*pPhysics;
extern RandomSeedFn         RandomSeed;
extern RandomIntFn          RandomInt;
extern SendClanTagFn        SetClanTag;
extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
extern IGameEventManager2* pGameEventManager;
extern INetChannelInfo*     nci;


extern VMT* paintVMT;
extern VMT* createmoveVMT;
extern VMT* clientVMT;
extern VMT* modelVMT;
extern VMT* predVMT;
extern VMT* materialVMT;
extern VMT* game_event_vmt;

extern RecvVarProxyFn g_pSequence;


