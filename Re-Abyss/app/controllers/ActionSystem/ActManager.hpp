#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    /// <summary>
    /// ActionSystem Manager
    /// </summary>
    class ActManager
    {
    private:
        World* m_pWorld = nullptr;
        Camera* m_pCamera = nullptr;
        Light* m_pLight = nullptr;

        PlayerActor* m_pPlayer = nullptr;
    public:
        ActManager& set(World* pWorld);

        ActManager& set(Camera* pCamera);

        ActManager& set(Light* pLight);

        ActManager& set(PlayerActor* pPlayer);

        template<class T>
        T* getModule() const;
    };
}