#if ABYSS_DEBUG
#include "DebugManager.hpp"
#include <Siv3D.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Visitor.hpp>

namespace abyss
{
    class DebugManager::Impl
    {
    public:
        bool m_isDrawColider = false;
        int m_frameRate = 60;
        void update()
        {
            if (Key1.down()) {
                m_isDrawColider = !m_isDrawColider;
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
            []([[maybe_unused]]const None_t&) {}
        }, colider);
    }
}

#endif