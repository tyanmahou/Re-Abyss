#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    /// <summary>
    /// System Manager
    /// </summary>
    class Manager
    {
    private:
        Master* m_pMaster = nullptr;
        GlobalTime* m_pGlobalTime = nullptr;
        World* m_pWorld = nullptr;
        PhysicsManager* m_pPhysics = nullptr;
        Events* m_pEvents = nullptr;
        Camera* m_pCamera = nullptr;
        Light* m_pLight = nullptr;
        Distortion* m_pDistortion = nullptr;
        Effects* m_pEffects = nullptr;
        Sound* m_pSound = nullptr;
        UIs* m_pUserInterface = nullptr;
        BackGround* m_pBackGround = nullptr;
        Decors* m_pDecors = nullptr;
        Stage* m_pStage = nullptr;
        Crons* m_pCrons = nullptr;
        Temporary* m_pTemporary = nullptr;
        Actor::Player::PlayerManager* m_pPlayer = nullptr;
        DrawManager* m_pDrawer = nullptr;
        CycleMaster* m_pCycleMaster = nullptr;
    public:
        Manager& set(Master* pMaster);

        Manager& set(GlobalTime* pGlobalTime);

        Manager& set(World* pWorld);

        Manager& set(PhysicsManager* pPhysics);

        Manager& set(Events* pEvents);

        Manager& set(Camera* pCamera);

        Manager& set(Light* pLight);

        Manager& set(Distortion* pDistortion);

        Manager& set(Effects* pEffects);

        Manager& set(Sound* pSound);

        Manager& set(UIs* pUIs);

        Manager& set(BackGround* pBackGround);

        Manager& set(Decors* pDecors);

        Manager& set(Stage* pStage);

        Manager& set(Crons* pCrons);

        Manager& set(Temporary* pTemporary);

        Manager& set(Actor::Player::PlayerManager* pPlayer);

        Manager& set(DrawManager* pDrawer);

        Manager& set(CycleMaster* pCycleMaster);

        template<class T>
        T* getModule() const;
    };
}