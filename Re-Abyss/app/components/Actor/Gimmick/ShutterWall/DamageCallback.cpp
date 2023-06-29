#include <abyss/components/Actor/Gimmick/ShutterWall/DamageCallback.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/components/Actor/Common/DeployId.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Enemy/SeDef.hpp>
#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Builder.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    TempKey ShutterWallBreakKey(ActorObj* pActor)
    {
        return TempKey::ShutterWallBreak(
            pActor->getModule<Stage>()->mapName(),
            pActor->find<DeployId>()->id()
        );
    }
}
namespace abyss::Actor::Gimmick::ShutterWall
{
    DamageCallback::DamageCallback(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void DamageCallback::onStart()
    {
        // 取得済みなら破棄
        if (m_pActor->getModule<Temporary>()->onFlag(::ShutterWallBreakKey(m_pActor))) {
            m_pActor->destroy();
            return;
        }
    }

    void DamageCallback::onDamaged([[maybe_unused]]const DamageData& damage) 
    {
        // ダメージ音
        m_pActor->find<AudioSource>()->playAt(Enemy::SeDef::Damage);
    }

    void DamageCallback::onDead()
    {
        // 死亡エフェクト
        m_pActor->getModule<Effects>()->createWorldFront<Effect::Actor::Gimmick::ShutterWall::Break::Builder>(
            m_pActor->find<ILocator>()->getCenterPos()
            );

        // 地震
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.3);

        // フラグ保存
        m_pActor->getModule<Temporary>()->saveFlagRestart(::ShutterWallBreakKey(m_pActor));
    }
}
