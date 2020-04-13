#include "ActManager.hpp"

namespace abyss
{
    ActManager& ActManager::set(World* pWorld)
    {
        m_pWorld = pWorld;
        return *this;
    }
    ActManager& ActManager::set(Camera* pCamera)
    {
        m_pCamera = pCamera;
        return *this;
    }
    ActManager& ActManager::set(Light* pLight)
    {
        m_pLight = pLight;
        return *this;
    }
    ActManager& ActManager::set(PlayerActor* pPlayer)
    {
        m_pPlayer = pPlayer;
        return *this;
    }

    template<class T>
    T* ActManager::getModule() const
    {
        if constexpr (std::is_same_v<World, T>) {
            return m_pWorld;
        } else if constexpr (std::is_same_v<Camera, T>) {
            return m_pCamera;
        } else if constexpr (std::is_same_v<Light, T>) {
            return m_pLight;
        } else if (std::is_same_v<PlayerActor, T>) {
            return m_pPlayer;
        }
    }
    template World* ActManager::getModule<World>() const;
    template Camera* ActManager::getModule<Camera>() const;
    template Light* ActManager::getModule<Light>() const;
    template PlayerActor* ActManager::getModule<PlayerActor>() const;

}
