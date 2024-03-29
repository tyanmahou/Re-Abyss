#include <abyss/modules/Manager/Manager.hpp>

namespace abyss
{
    Manager& Manager::set(GlobalTime* pGlobalTime)
    {
        m_pGlobalTime = pGlobalTime;
        return *this;
    }
    Manager& Manager::set(Actors* pActors)
    {
        m_pActors = pActors;
        return *this;
    }
    Manager& Manager::set(CollisionManager* pCollision)
    {
        m_pCollision = pCollision;
        return *this;
    }
    Manager& Manager::set(PhysicsManager* pPhysics)
    {
        m_pPhysics = pPhysics;
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
    Manager& Manager::set(Distortion* pDistortion)
    {
        m_pDistortion = pDistortion;
        return *this;
    }
    Manager& Manager::set(Effects* pEffects)
    {
        m_pEffects = pEffects;
        return *this;
    }
    Manager& Manager::set(Environment* pEnv)
    {
        m_pEnv = pEnv;
        return *this;
    }
    Manager& Manager::set(Sounds* pSounds)
    {
        m_pSounds = pSounds;
        return *this;
    }
    Manager& Manager::set(UIs* pUI)
    {
        m_pUserInterface = pUI;
        return *this;
    }
    Manager& Manager::set(Decors* pDecors)
    {
        m_pDecors = pDecors;
        return *this;
    }
    Manager& Manager::set(Stage* pStage)
    {
        m_pStage = pStage;
        return *this;
    }
    Manager& Manager::set(Crons* pCrons)
    {
        m_pCrons = pCrons;
        return *this;
    }
    Manager& Manager::set(Temporary* pTemporary)
    {
        m_pTemporary = pTemporary;
        return *this;
    }
    Manager& Manager::set(Actor::Player::PlayerManager* pPlayer)
    {
        m_pPlayer = pPlayer;
        return *this;
    }

    Manager& Manager::set(DrawManager* pDrawer)
    {
        m_pDrawer = pDrawer;
        return *this;
    }

    Manager& Manager::set(CycleMaster* pCycleMaster)
    {
        m_pCycleMaster = pCycleMaster;
        return *this;
    }
    Manager& Manager::set(RoomManager* pRoom)
    {
        m_pRoom = pRoom;
        return *this;
    }
    Manager& Manager::set(Adventures* pAdv)
    {
        m_pAdv = pAdv;
        return *this;
    }
    Manager& Manager::set(SpecialEffects* pSfx)
    {
        m_pSfx = pSfx;
        return *this;
    }

    Manager& Manager::set(PostEffects* pPostEffects)
    {
        m_pPostEffects = pPostEffects;
        return *this;
    }

    Manager& Manager::set(PauseManager* pPause)
    {
        m_pPause = pPause;
        return *this;
    }

    Manager& Manager::set(Storage* pStorage)
    {
        m_pStorage = pStorage;
        return *this;
    }

    Manager& Manager::set(Fader* pFader)
    {
        m_pFader = pFader;
        return *this;
    }
#if ABYSS_DEBUG
    Manager& Manager::set(WorldComment* pWorldComment)
    {
        m_pWorldComment = pWorldComment;
        return *this;
    }
#endif

#if ABYSS_DEVELOP
    Manager& Manager::set(Project* pProject)
    {
        m_pProject = pProject;
        return *this;
    }
#endif

    template<class T>
    T* Manager::getModule() const
    {
        if constexpr (std::is_same_v<GlobalTime, T>) {
            return m_pGlobalTime;
        } else if constexpr (std::is_same_v<Actors, T>) {
            return m_pActors;
        } else if constexpr (std::is_same_v<CollisionManager, T>) {
            return m_pCollision;
        } else if constexpr (std::is_same_v<PhysicsManager, T>) {
            return m_pPhysics;
        } else if constexpr (std::is_same_v<Events, T>) {
            return m_pEvents;
        } else if constexpr (std::is_same_v<Camera, T>) {
            return m_pCamera;
        } else if constexpr (std::is_same_v<Light, T>) {
            return m_pLight;
        } else if constexpr (std::is_same_v<Distortion, T>) {
            return m_pDistortion;
        } else if constexpr (std::is_same_v<Effects, T>) {
            return m_pEffects;
        } else if constexpr (std::is_same_v<Environment, T>) {
            return m_pEnv;
        } else if constexpr (std::is_same_v<Sounds, T>) {
            return m_pSounds;
        } else if constexpr (std::is_same_v<UIs, T>) {
            return m_pUserInterface;
        } else if constexpr (std::is_same_v<Decors, T>) {
            return m_pDecors;
        } else if constexpr (std::is_same_v<Stage, T>) {
            return m_pStage;
        } else if constexpr (std::is_same_v<Crons, T>) {
            return m_pCrons;
        } else if constexpr (std::is_same_v<Temporary, T>) {
            return m_pTemporary;
        } else if constexpr (std::is_same_v<Actor::Player::PlayerManager, T>) {
            return m_pPlayer;
        } else if constexpr (std::is_same_v<DrawManager, T>) {
            return m_pDrawer;
        } else if constexpr (std::is_same_v<CycleMaster, T>) {
            return m_pCycleMaster;
        } else if constexpr (std::is_same_v<RoomManager, T>) {
            return m_pRoom;
        } else if constexpr (std::is_same_v<Adventures, T>) {
            return m_pAdv;
        } else if constexpr (std::is_same_v<SpecialEffects, T>) {
            return m_pSfx;
        } else if constexpr (std::is_same_v<PostEffects, T>) {
            return m_pPostEffects;
        } else if constexpr (std::is_same_v<PauseManager, T>) {
            return m_pPause;
        } else if constexpr (std::is_same_v<Storage, T>) {
            return m_pStorage;
        } else if constexpr (std::is_same_v<Fader, T>) {
            return m_pFader;
        }
#if ABYSS_DEBUG
        else if constexpr (std::is_same_v<WorldComment, T>) {
            return m_pWorldComment;
        }
#endif
#if ABYSS_DEVELOP
        else if constexpr (std::is_same_v<Project, T>) {
            return m_pProject;
        }
#endif
    }
    template GlobalTime* Manager::getModule<GlobalTime>() const;
    template Actors* Manager::getModule<Actors>() const;
    template CollisionManager* Manager::getModule<CollisionManager>() const;
    template PhysicsManager* Manager::getModule<PhysicsManager>() const;
    template Events* Manager::getModule<Events>() const;
    template Camera* Manager::getModule<Camera>() const;
    template Light* Manager::getModule<Light>() const;
    template Distortion* Manager::getModule<Distortion>() const;
    template Effects* Manager::getModule<Effects>() const;
    template Environment* Manager::getModule<Environment>() const;
    template Sounds* Manager::getModule<Sounds>() const;
    template UIs* Manager::getModule<UIs>() const;
    template Decors* Manager::getModule<Decors>() const;
    template Stage* Manager::getModule<Stage>() const;
    template Crons* Manager::getModule<Crons>() const;
    template Temporary* Manager::getModule<Temporary>() const;
    template Actor::Player::PlayerManager* Manager::getModule<Actor::Player::PlayerManager>() const;
    template DrawManager* Manager::getModule<DrawManager>() const;
    template CycleMaster* Manager::getModule<CycleMaster>() const;
    template RoomManager* Manager::getModule<RoomManager>() const;
    template Adventures* Manager::getModule<Adventures>() const;
    template SpecialEffects* Manager::getModule<SpecialEffects>() const;
    template PostEffects* Manager::getModule<PostEffects>() const;
    template PauseManager* Manager::getModule<PauseManager>() const;
    template Storage* Manager::getModule<Storage>() const;
    template Fader* Manager::getModule<Fader>() const;
#if ABYSS_DEBUG
    template WorldComment* Manager::getModule<WorldComment>() const;
#endif
#if ABYSS_DEVELOP
    template Project* Manager::getModule<Project>() const;
#endif
}
