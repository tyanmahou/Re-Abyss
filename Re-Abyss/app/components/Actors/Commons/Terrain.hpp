#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
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

        bool accept(const ActVisitor& visit) const;
    };
}