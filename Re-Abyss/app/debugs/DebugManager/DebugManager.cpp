#if ABYSS_DEBUG
#include "DebugManager.hpp"
#include <Siv3D.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Visitor.hpp>
#include <abyss/modules/Effects/Effects.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actors/base/ICollision.hpp>
#include <abyss/components/Actors/base/IPhysics.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>

#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/debugs/Util/DebugUtil.hpp>

namespace abyss::Debug
{
    class DebugManager::Impl
    {
    public:

        bool m_showFps = false;
        void update()
        {
            if (KeyF7.down()) {
                m_showFps ^= true;
            }
            if (m_showFps) {
                Log::Print << Profiler::FPS();
            }
        }

        void drawCollider(const World& world)
        {
            if (!Menu::IsDebug(U"draw-collider")) {
                return;
            }
            auto colliders = world.finds<Actor::ICollision>();
            Log::Print << U"Colliders: " << colliders.size();

            constexpr ColorF color = ColorF(1, 0, 0, 0.4);

            for (auto&& col : colliders) {
                if (!col->isActive()) {
                    continue;
                }
                DebugUtil::DrawShape(col->getCollider(), color);
            }
        }
        void drawMapCollider(const World& world)
        {
            if (!Menu::IsDebug(U"draw-map-collider")) {
                return;
            }

            constexpr ColorF color = ColorF(0, 0, 1, 0.4);
            {
                auto colliders = world.finds<Actor::IPhysics>();
                Log::Print << U"Map Colliders: " << colliders.size();

                for (auto&& col : colliders) {
                    if (!col->isActive()) {
                        continue;
                    }
                    DebugUtil::DrawShape(col->getCollider(), color);
                }
            }
            {
                auto terrains = world.finds<Actor::Terrain>();
                Log::Print << U"Map Terrain: " << terrains.size();

                for (auto&& terrain : terrains) {
                    if (!terrain->isActive()) {
                        continue;
                    }
                    const auto& [region, col] = terrain->getMapColInfo();
                    const Vec2 qSize = {
                        Min(10.0, region.size.x / 4.0),
                        Min(10.0, region.size.y / 4.0)
                    };
                    if (col.isUp()) {
                        RectF(region.x, region.y, region.w, qSize.y).draw(color);
                    }
                    if (col.isDown()) {
                        RectF(region.x, region.y + region.h, region.w, -qSize.y).draw(color);
                    }
                    if (col.isLeft()) {
                        RectF(region.x, region.y, qSize.x, region.h).draw(color);
                    }
                    if (col.isRight()) {
                        RectF(region.x + region.w, region.y, -qSize.x, region.h).draw(color);
                    }
                }
            }
        }
    };
    DebugManager::DebugManager():
        m_pImpl(std::make_unique<Impl>())
    {}

    void DebugManager::Update()
    {
        return Instance()->m_pImpl->update();
    }

    void DebugManager::DrawDebug(const World& world)
    {
        auto& impl = Instance()->m_pImpl;
        impl->drawCollider(world);
        impl->drawMapCollider(world);
    }
    void DebugManager::DrawDebug(const Effects& effects)
    {
        if (!Debug::Menu::IsDebug(U"log-effect-num")) {
            return;
        }

        Log::Print << U"DecorBack: "  << effects.num<EffectGroup::DecorBack>();
        Log::Print << U"WorldBack: "  << effects.num<EffectGroup::WorldBack>();
        Log::Print << U"WorldFront: " << effects.num<EffectGroup::WorldFront>();
        Log::Print << U"DecorFront: " << effects.num<EffectGroup::DecorFront>();
    }
}

#endif