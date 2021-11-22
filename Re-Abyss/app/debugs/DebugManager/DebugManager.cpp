#if ABYSS_DEBUG
#include "DebugManager.hpp"
#include <Siv3D.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Visitor.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>

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
                Debug::Log.Update << Profiler::FPS();
            }
        }

        void drawCollider(const World& world)
        {
            if (!Menu::IsDebug(Debug::DebugFlag::DrawCollider)) {
                return;
            }
            auto coms = world.finds<Actor::Collider>();

            constexpr ColorF color = ColorF(1, 0, 0, 0.4);
            size_t size{};
            for (auto&& com : coms) {
                for (const auto& c : *com) {
                    DebugUtil::DrawShape(c->getCollider(), color);
                    ++size;
                }
            }
            Debug::Log.Update << U"Colliders: " << size;
        }
        void drawMapCollider(const PhysicsManager& physics)
        {
            if (!Menu::IsDebug(Debug::DebugFlag::DrawMapCollider)) {
                return;
            }

            constexpr ColorF color = ColorF(0, 0, 1, 0.4);
            {
                const auto& colliders = physics.getContacters();
                Debug::Log.Update << U"Map Colliders: " << colliders.size();

                for (auto&& col : colliders) {
                    if (!col->isActive()) {
                        continue;
                    }
                    DebugUtil::DrawShape(col->getShape(), color);
                }
            }
            {
                const auto& terrains = physics.getTerrains();
                Debug::Log.Update << U"Map Terrain: " << terrains.size();

                for (auto&& terrain : terrains) {
                    if (!terrain->isActive()) {
                        continue;
                    }
                    const auto& data = terrain->getData();
                    const auto& region = data.region;
                    const auto& col = data.col;

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
        Instance()->m_pImpl->drawCollider(world);
    }
    void DebugManager::DrawDebug(const PhysicsManager& physics)
    {
        Instance()->m_pImpl->drawMapCollider(physics);
    }
    void DebugManager::DrawDebug(const Effects& effects)
    {
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::AlertEffectCount)) {
            return;
        }
        Debug::Log.Update << U"---LogEffectCount---";
        Debug::Log.Update << U"Effect: "  << effects.size();
    }
    void DebugManager::DrawDebug(const Decors& decor)
    {
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::AlertDecorCount)) {
            return;
        }
        Debug::Log.Update << U"---LogDecorCount---";
        Debug::Log.Update << U"Decor: " << decor.size();
    }
    void DebugManager::AlertDrawerCount(const DrawManager* drawManager)
    {
        if (!drawManager) {
            return;
        }
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::AlertDrawerCount)) {
            return;
        }
        Debug::Log.Update << U"---LogDrawerCount---";
        for (DrawLayer layer = DrawLayer::BackGround;  layer < DrawLayer::Size; ++layer) {
            Debug::Log.Update << U"{}: {}"_fmt(Enum::ToStrView(layer), drawManager->size(layer));
        }
    }
}

#endif