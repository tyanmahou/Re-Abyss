#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor
{
    class Terrain : 
        public IComponent
    {
    private:
        IActor* m_pActor;
        MapColInfo m_mapColInfo;
        bool m_isActive = true;
    public:
        Terrain(IActor* pActor):
            m_pActor(pActor)
        {}

        Terrain& setMapColInfo(const MapColInfo& mapColInfo)
        {
            m_mapColInfo = mapColInfo;
            return *this;
        }

        const MapColInfo& getMapColInfo() const
        {
            return m_mapColInfo;
        }

        Terrain& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }

        bool isActive() const;

        IActor* getActor()const
        {
            return m_pActor;
        }

        template<Tag::Tagged T>
        bool isThen(std::function<bool(IActor*)> callback) const
        {
            return m_pActor->isThen<T>(callback);
        }
        template<Tag::Tagged T, IsComponent C>
        bool isThen(std::function<bool(C&)> callback) const
        {
            return m_pActor->isThen<T, C>(callback);
        }
        template<Tag::Tagged T>
        bool isNotThen(std::function<bool(IActor*)> callback) const
        {
            return m_pActor->isNotThen<T>(callback);
        }
    };
}