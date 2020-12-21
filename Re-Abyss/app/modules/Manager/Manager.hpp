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
        Events* m_pEvents = nullptr;
        Camera* m_pCamera = nullptr;
        Light* m_pLight = nullptr;
        Effects* m_pEffects = nullptr;
        Sound* m_pSound = nullptr;
        UI* m_pUserInterface = nullptr;
        BackGround* m_pBackGround = nullptr;
        Decor* m_pDecor = nullptr;
        Stage* m_pStage = nullptr;
        Cron* m_pCron = nullptr;
        Save* m_pSave = nullptr;
        Actor::Player::PlayerManager* m_pPlayer = nullptr;
    public:
        Manager& set(Master* pMaster);

        Manager& set(GlobalTime* pGlobalTime);

        Manager& set(World* pWorld);

        Manager& set(Events* pEvents);

        Manager& set(Camera* pCamera);

        Manager& set(Light* pLight);

        Manager& set(Effects* pEffects);

        Manager& set(Sound* pSound);

        Manager& set(UI* pUI);

        Manager& set(BackGround* pBackGround);

        Manager& set(Decor* pDecor);

        Manager& set(Stage* pStage);

        Manager& set(Cron* pCron);

        Manager& set(Save* pSave);

        Manager& set(Actor::Player::PlayerManager* pPlayer);

        template<class T>
        T* getModule() const;
    };
}