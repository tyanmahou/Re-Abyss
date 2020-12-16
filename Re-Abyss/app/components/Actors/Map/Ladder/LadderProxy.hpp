#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actors/Map/MapParam.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>

namespace abyss::Actor::Map::Ladder
{
    class LadderProxy :
        public IComponent
    {
    public:
        LadderProxy(IActor* pActor);

        void setup([[maybe_unused]] Depends depends) override;

        void onStart() override;

        s3d::Line getCenterLine() const;
        bool isTop() const;
    private:
        IActor* m_pActor;
        Ref<MapParam> m_mapParam;
        Ref<Terrain> m_terrain;
    };
}