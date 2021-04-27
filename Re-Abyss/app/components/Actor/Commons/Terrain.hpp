#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor
{
    class Terrain : 
        public IComponent
    {
    private:
        ActorObj* m_pActor;
        MapColInfo m_mapColInfo;
        bool m_isActive = true;
    public:
        Terrain(ActorObj* pActor):
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

        ActorObj* getActor()const
        {
            return m_pActor;
        }

        template<Tag::Tagged T>
        bool isThen(std::function<bool(ActorObj*)> callback) const
        {
            return m_pActor->isThen<T>(callback);
        }
        template<Tag::Tagged T, IsComponent C>
        bool isThen(std::function<bool(C&)> callback) const
        {
            return m_pActor->isThen<T, C>(callback);
        }
        template<Tag::Tagged T>
        bool isNotThen(std::function<bool(ActorObj*)> callback) const
        {
            return m_pActor->isNotThen<T>(callback);
        }
    };
}