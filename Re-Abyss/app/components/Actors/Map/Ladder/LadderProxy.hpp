#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actors/Map/MapProxy.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>

namespace abyss::Actor::Map::Ladder
{
    class LadderProxy :
        public IComponent
    {
    public:
        LadderProxy(IActor* pActor);

        void setup([[maybe_unused]] Executer executer) override;

        void onStart() override;

        const s3d::Vec2& getPos() const;
        s3d::RectF region() const;
        s3d::Line getCenterLine() const;
        bool isTop() const;

        s3d::Vec2 getCenterTopPos() const;
    private:
        IActor* m_pActor;
        Ref<MapProxy> m_map;
        Ref<Terrain> m_terrain;
    };
}