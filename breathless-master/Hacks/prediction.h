#ifndef EnginePrediction_h
#define EnginePrediction_h

#include "main.h"

extern float m_flOldCurtime;
extern float m_flOldFrametime;

class CEnginePrediction {
public:
    CEnginePrediction();
    static CEnginePrediction* Instance() {
        if (!instance) {
            instance = new CEnginePrediction();
        }
        
        return instance;
    }
    static std::map<int, const char*> GetModeList();
    static std::map<int, const char*> GetModeValues();
    void StartSingle(CUserCmd* cmd, C_BaseCombatWeapon* pWeapon, C_BaseEntity* pLocal);
    void Start(CUserCmd* cmd);
    void End();
private:
    static CEnginePrediction* instance;
    float m_flOldCurtime = 0.f;
    float m_flOldFrametime = 0.f;
    int oldPFlags;
};

#endif /* EnginePrediction_h */
