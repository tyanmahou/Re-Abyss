#pragma once

#include <abyss/views/Actor/Ooparts/base/BaseVM.hpp>

namespace abyss::Actor::Player
{
    class XtoAtkVM : public Ooparts::BaseVM
    {
        std::function<void()> m_callback;
        void draw([[maybe_unused]] const s3d::ColorF& color) const override
        {
            if (m_callback) {
                m_callback();
            }
        }
        s3d::TextureRegion icon() const
        {
            return  s3d::TextureRegion();
        }
    public:
        XtoAtkVM& setDrawFunc(const std::function<void()>& callback)
        {
            m_callback = callback;
            return *this;
        }
    };
}