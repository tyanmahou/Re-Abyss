#include <abyss/components/Effect/Actor/Common/EnemyDead/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/views/Effect/Actor/Common/EnemyDeadVM.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::EnemyDead
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_view(std::make_unique<Actor::EnemyDeadVM>())
    {
        m_view->setPos(pos);
    }

    Main::~Main()
    {}

    bool Main::onDraw(double time)
    {
        time *= 2.0;
        m_view
            ->setAnimRate(time)
            .draw();
        ;
        return time <= 1.0;
    }
}