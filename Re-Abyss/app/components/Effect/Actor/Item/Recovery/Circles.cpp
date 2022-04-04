#include <abyss/components/Effect/Actor/Item/Recovery/Circles.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/ColorDef.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    Circles::Circles(EffectObj* pObj) :
        m_pObj(pObj),
        m_startAngle(Random()* Math::TwoPi)
    {}

    Circles::~Circles()
    {}

    void Circles::onStart()
    {
        m_location = m_pObj->find<LocationCtrl>();
    }

    bool Circles::onDraw(double time)
    {
        const auto& pos = m_location->getPos();

        const bool colorFrame = (static_cast<int32>(Periodic::Sawtooth0_1(0.25, time) * 2.0) % 2) == 1;
        {
            auto rate = s3d::EaseOutQuart(time);
            ColorF color = colorFrame ? Color0 : Color1;
            Circle(pos, 36.0 * rate).drawArc(m_startAngle + s3d::Math::Pi - s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 1.0, 1.0, color.setA(1.0 - rate));
        }
        {
            auto rate = s3d::EaseOutExpo(time);
            ColorF color = colorFrame ? Color1 : Color0;
            Circle(pos, 40.0 * rate).drawArc(m_startAngle + s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 2.0, 1.0, color.setA(1.0 - rate));
        }
        {
            auto rate = s3d::EaseOutExpo(time);
            ColorF color = colorFrame ? Color0 : Color1;
            Circle(pos, 45.0 * rate).drawArc(m_startAngle + s3d::Math::HalfPi + s3d::Math::Pi * rate, s3d::Math::ToRadians(270.0), 1.0, 0.0, color.setA(1.0 - rate));
        }
        {
            auto rate = s3d::EaseOutQuad(time);
            Circle(pos, 45.0 * rate).drawFrame(1.0, ColorF(1, 1.0 - rate));
        }
        return time <= 1.0;
    }
}