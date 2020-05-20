#include "XtoVM.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss::Xto
{
    XtoVM::XtoVM():
        m_texture(ResourceManager::Main()->loadTexture(U"actors/Ooparts/Xto/xto.png")),
        m_pos(0, 0),
        m_forward(Forward::Right)
    {}

    void XtoVM::draw() const
    {
        auto time = WorldTime::Time();
        auto pos = m_pos + Circular(10, time * 4.0).toVec2();
        ColorF color = Palette::White;
        double a = 0.4 * Periodic::Triangle0_1(0.1s, time);
        constexpr double period = 0.8;
        {
            ScopedRenderStates2D t2d(BlendState::Additive);

            Circle(pos, 17 * (1 - Periodic::Sawtooth0_1(period, time))).drawFrame(0, 1, color.setA(a));
            double s = 25 * Periodic::Triangle0_1(period /2.0, time);
            RectF({ 0,0,s, s })
                .setCenter(pos)
                .rotated(Math::QuarterPi * Periodic::Square0_1(period, time))
                .drawFrame(0, 1, color.setA(0.5 - a));
        }
        {
            auto c = static_cast<s3d::int32>(time * 10.0) % 2 ? s3d::ColorF(1.0, 0.5) : s3d::ColorF(0.9);
            bool isRight = m_forward == Forward::Right;
            int32 page = static_cast<int32>(Periodic::Square0_1(1s, time)) % 2;
            m_texture({ 0, 20 * page }, { 20, 20 }).mirrored(isRight).drawAt(pos);
        }
        {
            ScopedRenderStates2D t2d(BlendState::Additive);
            Circle(pos, Periodic::Triangle0_1(period / 2.0, time) * 5 + 10).draw(color.setA(a));
        }
    }

}
