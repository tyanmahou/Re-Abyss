#if ABYSS_DEBUG
#include "DebugManager.hpp"
#include <Siv3D.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Visitor.hpp>
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>
#include <abyss/models/Actors/base/IPhysicsModel.hpp>
#include <abyss/models/Actors/Commons/TerrainModel.hpp>

#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Debug
{
    class DebugManager::Impl
    {
    public:
        bool m_isDrawColider = false;
        bool m_isDrawMapColider = false;
        bool m_disableDarkNess = false;
        bool m_isLogEffectNum = false;
        int m_frameRate = 60;

        bool m_showFps = false;
        void update()
        {
            if (Key1.down()) {
                m_isDrawColider = !m_isDrawColider;
            }
            if (Key2.down()) {
                m_isDrawMapColider = !m_isDrawMapColider;
            }
            if (Key3.down()) {
                m_isLogEffectNum = !m_isLogEffectNum;
            }
            if (Key4.down()) {
                m_disableDarkNess = !m_disableDarkNess;
            }
            if ((KeyF + KeyDown).down() && m_frameRate > 1) {
                Graphics::SetTargetFrameRateHz(--m_frameRate);
            }
            if ((KeyF + KeyUp).down()) {
                Graphics::SetTargetFrameRateHz(++m_frameRate);
            }
            if ((KeyF + KeyEnter).down()) {
                m_frameRate = 60;
                Graphics::SetTargetFrameRateHz(s3d::none);
            }
            if (KeyF7.down()) {
                m_showFps ^= true;
            }
            if (m_showFps) {
                Log::Print << Profiler::FPS();
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

    bool DebugManager::IsDrawColider()
    {
        return Instance()->m_pImpl->m_isDrawColider;
    }
    bool DebugManager::IsDrawMapColider()
    {
        return Instance()->m_pImpl->m_isDrawMapColider;
    }
    bool DebugManager::DisableDarkNess()
    {
        return Instance()->m_pImpl->m_disableDarkNess;
    }
    void DebugManager::DrawColider(const CShape& colider, const s3d::ColorF& color)
    {
        std::visit(overloaded{
            [&color](const auto& c) {
                c.draw(color);
            },
            [&color](const Vec2& c) {
                Shape2D::Cross(5, 2, c).draw(color);
            },
            [&color](const Array<CShape>& c) {
                for (const auto& shape : c) {
                    DebugManager::DrawColider(shape, color);
                }
            },

            []([[maybe_unused]]const None_t&) {}
        }, colider);
    }
    void DebugManager::DrawColider(const World& world)
    {
        if (!IsDrawColider()) {
            return;
        }

        auto colliders = world.finds<IColliderModel>();
        Log::Print << U"Colliders: " << colliders.size();

        constexpr ColorF color = ColorF(1, 0, 0, 0.4);

        for (auto&& col : colliders) {
            if (!col->isActive()) {
                continue;
            }
            DrawColider(col->getCollider(), color);
        }
    }
    void DebugManager::DrawMapColider(const World & world)
    {
        if (!IsDrawMapColider()) {
            return;
        }
        constexpr ColorF color = ColorF(0, 0, 1, 0.4);
        {
            auto colliders = world.finds<IPhysicsModel>();
            Log::Print << U"Map Colliders: " << colliders.size();

            for (auto&& col : colliders) {
                if (!col->isActive()) {
                    continue;
                }
                auto collider = col->getCollider();
                CShape shape = collider;
                if (collider.size.isZero()) {
                    shape = collider.center();
                }
                DrawColider(shape, color);
            }
        }
        {
            auto terrains = world.finds<TerrainModel>();
            Log::Print << U"Map Terrain: " << terrains.size();

            for (auto&& terrain : terrains) {
                if (!terrain->isActive()) {
                    continue;
                }
                const auto&[region, col] = terrain->getMapColInfo();
                if (col.isUp()) {
                    RectF(region.x, region.y, region.w, region.h / 4.0).draw(color);
                }
                if (col.isDown()) {
                    RectF(region.x, region.y + region.h, region.w, -region.h / 4.0).draw(color);
                }
                if (col.isLeft()) {
                    RectF(region.x, region.y, region.w / 4.0, region.h).draw(color);
                }
                if (col.isRight()) {
                    RectF(region.x + region.w, region.y, -region.w / 4.0, region.h).draw(color);
                }
            }
        }
    }
    bool DebugManager::IsLogEffectNum()
    {
        return Instance()->m_pImpl->m_isLogEffectNum;
    }
    void DebugManager::LogEffectNum(const Effects& effects)
    {
        Log::Print << U"DecorBack: "  << effects.num<EffectGroup::DecorBack>();
        Log::Print << U"WorldBack: "  << effects.num<EffectGroup::WorldBack>();
        Log::Print << U"WorldFront: " << effects.num<EffectGroup::WorldFront>();
        Log::Print << U"DecorFront: " << effects.num<EffectGroup::DecorFront>();
    }
}

#endif