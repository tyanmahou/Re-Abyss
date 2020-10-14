#pragma once

#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>

namespace abyss::Actor::Player
{
    class XtoAtkVM : public Ooparts::OopartsVM
    {
        std::function<void()> m_callback;
        void drawCharacter([[maybe_unused]] const s3d::Vec2& pos, [[maybe_unused]] const s3d::ColorF& color) const override
        {
            if (m_callback) {
                m_callback();
            }
        }
    public:
        XtoAtkVM& setDrawFunc(const std::function<void()>& callback)
        {
            m_callback = callback;
            return *this;
        }
    };
}