#include "Builder.hpp"

#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>

#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actors/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actors/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/components/Actors/Enemy/RollingTako/State/RunState.hpp>


namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::RollingTako
{
    void Builder::Build(ActorObj* pActor, const RollingTakoEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true)
            .setAudioSettingGroupPath(U"Enemy/RollingTako/rolling_tako.aase")
        );

        // 初期状態
        {
            auto stateCtrl = pActor->find<StateCtrl>();
            if (entity.wait) {
                stateCtrl->changeState<WaitState>();
            } else {
                stateCtrl->changeState<RunState>();
            }
        }

        // Body調整
        {
            pActor->find<Body>()->setMaxSpeedX(Param::Run::MaxSpeedX);
        }
        // ルーム外死亡
        {
            pActor->attach<OutRoomChecker>(pActor);
        }
        // 描画
        {
            pActor->attach<ViewCtrl<RollingTakoVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::RollingTako;

    class ViewBinder : public ViewCtrl<RollingTakoVM>::IBinder
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;

        std::unique_ptr<RollingTakoVM> m_view;
    private:
        RollingTakoVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<RollingTakoVM>())
        {}
    };
}
