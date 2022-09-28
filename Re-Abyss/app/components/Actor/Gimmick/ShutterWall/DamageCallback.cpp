#include <abyss/components/Actor/Gimmick/ShutterWall/DamageCallback.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Camera/Camera.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    DamageCallback::DamageCallback(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void DamageCallback::onDamaged([[maybe_unused]]const DamageData& damage) 
    {
        // TODO ダメージ音鳴らす
    }

    void DamageCallback::onDead()
    {
        // TODO 死亡エフェクト

        // 地震
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.3);
    }
}
