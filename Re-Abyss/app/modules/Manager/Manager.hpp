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
        GlobalTime* m_pGlobalTime = nullptr;
        Actors* m_pActors = nullptr;
        CollisionManager* m_pCollision = nullptr;
        PhysicsManager* m_pPhysics = nullptr;
        Events* m_pEvents = nullptr;
        Camera* m_pCamera = nullptr;
        Light* m_pLight = nullptr;
        Distortion* m_pDistortion = nullptr;
        Effects* m_pEffects = nullptr;
        Environment* m_pEnv = nullptr;
        Sound* m_pSound = nullptr;
        UIs* m_pUserInterface = nullptr;
        Decors* m_pDecors = nullptr;
        Stage* m_pStage = nullptr;
        Crons* m_pCrons = nullptr;
        Temporary* m_pTemporary = nullptr;
        Actor::Player::PlayerManager* m_pPlayer = nullptr;
        DrawManager* m_pDrawer = nullptr;
        CycleMaster* m_pCycleMaster = nullptr;
        RoomManager* m_pRoom = nullptr;
        Adventures* m_pAdv = nullptr;
        SpecialEffects* m_pSfx = nullptr;
        PostEffects* m_pPostEffects = nullptr;
        PauseManager* m_pPause = nullptr;
#if ABYSS_DEBUG
        WorldComment* m_pWorldComment = nullptr;
#endif
#if ABYSS_DEVELOP
        Project* m_pProject = nullptr;
#endif
    public:

        Manager& set(GlobalTime* pGlobalTime);

        Manager& set(Actors* pActors);

        Manager& set(CollisionManager* pCollision);

        Manager& set(PhysicsManager* pPhysics);

        Manager& set(Events* pEvents);

        Manager& set(Camera* pCamera);

        Manager& set(Light* pLight);

        Manager& set(Distortion* pDistortion);

        Manager& set(Effects* pEffects);

        Manager& set(Environment* pEnv);

        Manager& set(Sound* pSound);

        Manager& set(UIs* pUIs);

        Manager& set(Decors* pDecors);

        Manager& set(Stage* pStage);

        Manager& set(Crons* pCrons);

        Manager& set(Temporary* pTemporary);

        Manager& set(Actor::Player::PlayerManager* pPlayer);

        Manager& set(DrawManager* pDrawer);

        Manager& set(CycleMaster* pCycleMaster);

        Manager& set(RoomManager* pRoom);

        Manager& set(Adventures* pAdv);

        Manager& set(SpecialEffects* pSfx);
        Manager& set(PostEffects* pPostEffects);

        Manager& set(PauseManager* pPause);


#if ABYSS_DEBUG
        Manager& set(WorldComment* pWorldComment);
#endif

#if ABYSS_DEVELOP
        Manager& set(Project* pProject);
#endif
        template<class T>
        T* getModule() const;
    };
}
