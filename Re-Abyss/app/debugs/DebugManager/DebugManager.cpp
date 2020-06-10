#if ABYSS_DEBUG
#include "DebugManager.hpp"
#include <Siv3D.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Visitor.hpp>
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Debug
{
    class DebugManager::Impl
    {
    public:
        bool m_isDrawColider = false;
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
                m_disableDarkNess = !m_disableDarkNess;
            }
            if (Key3.down()) {
                m_isLogEffectNum = !m_isLogEffectNum;
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
    bool DebugManager::DisableDarkNess()
    {
        return Instance()->m_pImpl->m_disableDarkNess;
    }
    void DebugManager::DrawColider(const CShape& colider)
    {
        constexpr ColorF color = ColorF(1, 0, 0, 0.4);
        std::visit(overloaded{
            [&color](const auto& c) {
                c.draw(color);
            },
            [&color](const Vec2& c) {
                Shape2D::Cross(5, 2, c).draw(color);
            },
            [&color](const Array<CShape>& c) {
                for (const auto& shape : c) {
                    DebugManager::DrawColider(shape);
                }
            },

            []([[maybe_unused]]const None_t&) {}
        }, colider);
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