#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss
{
    class TerrainModel : 
        public IComponent
    {
    private:
        IActor* m_pActor;
        MapColInfo m_mapColInfo;
        bool m_isActive = true;
    public:
        TerrainModel(IActor* pActor):
            m_pActor(pActor)
        {}

        TerrainModel& setMapColInfo(const MapColInfo& mapColInfo)
        {
            m_mapColInfo = mapColInfo;
            return *this;
        }

        const MapColInfo& getMapColInfo() const
        {
            return m_mapColInfo;
        }

        TerrainModel& setActive(bool isActive)
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