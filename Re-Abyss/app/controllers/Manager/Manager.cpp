#include "Manager.hpp"

namespace abyss
{
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
    Manager& Manager::set(Sound* pSound)
    {
        m_pSound = pSound;
        return *this;
    }
    Manager& Manager::set(Player::PlayerActor* pPlayer)
    {
        m_pPlayer = pPlayer;
        return *this;
    }

    template<class T>
    T* Manager::getModule() const
    {
        if constexpr (std::is_same_v<World, T>) {
            return m_pWorld;
        } else if constexpr (std::is_same_v<Events, T>) {
            return m_pEvents;
        } else if constexpr (std::is_same_v<Camera, T>) {
            return m_pCamera;
        } else if constexpr (std::is_same_v<Light, T>) {
            return m_pLight;
        } else if constexpr (std::is_same_v<Sound, T>) {
            return m_pSound;
        } else if (std::is_same_v<Player::PlayerActor, T>) {
            return m_pPlayer;
        }
    }
    template World* Manager::getModule<World>() const;
    template Events* Manager::getModule<Events>() const;
    template Camera* Manager::getModule<Camera>() const;
    template Light* Manager::getModule<Light>() const;
    template Sound* Manager::getModule<Sound>() const;
    template Player::PlayerActor* Manager::getModule<Player::PlayerActor>() const;

}
