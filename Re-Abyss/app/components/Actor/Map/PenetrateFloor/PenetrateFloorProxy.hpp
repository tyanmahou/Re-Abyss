#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actor/Map/MapProxy.hpp>
#include <abyss/components/Actor/Commons/Terrain.hpp>

namespace abyss::Actor::Map::PenetrateFloor
{
    class PenetrateFloorProxy :
        public IComponent
    {
    public:
        PenetrateFloorProxy(ActorObj* pActor, bool canDown, ColDirection aroundFloor);

        void setup(Executer executer) override;

        void onStart() override;

        const s3d::Vec2& getPos() const;
        s3d::RectF region() const;

        bool canDown() const;

        bool tryDown(const s3d::RectF& region) const;
    private:
        ActorObj* m_pActor;
        bool m_canDown;
        ColDirection m_aroundFloor;

        Ref<MapProxy> m_map;
        Ref<Terrain> m_terrain;
    };
}