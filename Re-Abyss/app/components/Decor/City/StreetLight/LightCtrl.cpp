#include "LightCtrl.hpp"

#include <abyss/components/Decor/Commons/DecorInfo.hpp>
#include <abyss/components/Decor/Commons/BasicDraw.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/views/Decor/City/StreetLight/LightVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Decor::City::StreetLight
{
    LightCtrl::LightCtrl(DecorObj* pObj):
        m_pObj(pObj),
        m_view(std::make_unique<LightVM>())
    {}

    void LightCtrl::setup(Executer executer)
    {
        executer.on<IDraw>().addBefore<BasicDraw>();
    }

    void LightCtrl::onStart()
    {
        m_info = m_pObj->find<DecorInfo>();
    }
    void LightCtrl::onDraw() const
    {
        constexpr float radius = 50.0;
        auto time = m_pObj->getModule<GlobalTime>()->time();
        const auto pos = m_info->parallaxPos() + Vec2{ -10, -130.0 };
        m_view
            ->setPos(pos)
            .setRadius(radius)
            .setTime(time)
            .draw();
        m_pObj->getModule<Light>()->addCircle(pos, radius * 2.5);
        m_pObj->getModule<Light>()->addArc(
            pos + Vec2{ 10, -10 },
            radius * 6.0,
            40.0f,
            Math::ToRadians(185.0),
            Math::ToRadians(30.0),
            0.5
        );
    }
}