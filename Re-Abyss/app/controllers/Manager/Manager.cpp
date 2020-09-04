#include "Manager.hpp"

namespace abyss
{
    Manager& Manager::set(Master* pMaster)
    {
        m_pMaster = pMaster;
        return *this;
    }
    Manager& Manager::set(GlobalTime* pGlobalTime)
    {
        m_pGlobalTime = pGlobalTime;
        return *this;
    }
    Manager& Manager::set(World* pWorld)
    {
        m_pWorld = pWorld;
        return *this;
    }
    Manager& Manager::set(Events* pEvents)
    {
        m_pEvents = pEvents;
        return *this;
    }
    Manager& Manager::set(Camera* pCamera)
    {
        m_pCamera = pCamera;
        return *this;
    }
    Manager& Manager::set(Light* pLight)
    {
        m_pLight = pLight;
        return *this;
    }
    Manager& Manager::set(Effects* pEffects)
    {
        m_pEffects = pEffects;
        return *this;
    }
    Manager& Manager::set(Sound* pSound)
    {
        m_pSound = pSound;
        return *this;
    }
    Manager& Manager::set(UI* pUI)
    {
        m_pUserInterface = pUI;
        return *this;
    }
    Manager& Manager::set(BackGround* pBackGround)
    {
        m_pBackGround = pBackGround;
        return *this;
    }
    Manager& Manager::set(Decor* pDecor)
    {
        m_pDecor = pDecor;
        return *this;
    }
    Manager& Manager::set(Stage* pStage)
    {
        m_pStage = pStage;
        return *this;
    }
    Manager& Manager::set(Cron* pCron)
    {
        m_pCron = pCron;
        return *this;
    }
    Manager& Manager::set(Save* pSave)
    {
        m_pSave = pSave;
        return *this;
    }
    Manager& Manager::set(Actor::Player::PlayerActor* pPlayer)
    {
        m_pPlayer = pPlayer;
        return *this;
    }

    template<class T>
    T* Manager::getModule() const
    {
        if constexpr (std::is_same_v<Master, T>) {
            return m_pMaster;
        } else if constexpr (std::is_same_v<GlobalTime, T>) {
            return m_pGlobalTime;
        } else if constexpr (std::is_same_v<World, T>) {
            return m_pWorld;
        } else if constexpr (std::is_same_v<Events, T>) {
            return m_pEvents;
        } else if constexpr (std::is_same_v<Camera, T>) {
            return m_pCamera;
        } else if constexpr (std::is_same_v<Light, T>) {
            return m_pLight;
        } else if constexpr (std::is_same_v<Effects, T>) {
            return m_pEffects;
        } else if constexpr (std::is_same_v<Sound, T>) {
            return m_pSound;
        } else if constexpr (std::is_same_v<UI, T>) {
            return m_pUserInterface;
        } else if constexpr (std::is_same_v<BackGround, T>) {
            return m_pBackGround;
        } else if constexpr (std::is_same_v<Decor, T>) {
            return m_pDecor;
        } else if constexpr (std::is_same_v<Stage, T>) {
            return m_pStage;
        } else if constexpr (std::is_same_v<Cron, T>) {
            return m_pCron;
        } else if constexpr (std::is_same_v<Save, T>) {
            return m_pSave;
        } else if (std::is_same_v<Actor::Player::PlayerActor, T>) {
            return m_pPlayer;
        }
    }
    template Master* Manager::getModule<Master>() const;
    template GlobalTime* Manager::getModule<GlobalTime>() const;
    template World* Manager::getModule<World>() const;
    template Events* Manager::getModule<Events>() const;
    template Camera* Manager::getModule<Camera>() const;
    template Light* Manager::getModule<Light>() const;
    template Effects* Manager::getModule<Effects>() const;
    template Sound* Manager::getModule<Sound>() const;
    template UI* Manager::getModule<UI>() const;
    template BackGround* Manager::getModule<BackGround>() const;
    template Decor* Manager::getModule<Decor>() const;
    template Stage* Manager::getModule<Stage>() const;
    template Cron* Manager::getModule<Cron>() const;
    template Save* Manager::getModule<Save>() const;
    template Actor::Player::PlayerActor* Manager::getModule<Actor::Player::PlayerActor>() const;

}
