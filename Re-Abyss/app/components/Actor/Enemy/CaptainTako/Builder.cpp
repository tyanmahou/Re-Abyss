#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Enemy/CaptainTakoEntity.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>

#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Commons/VModel.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/State/WaitState.hpp>
#include <abyss/views/Actor/Enemy/CaptainTako/CpatainTakoVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CaptainTako
{
    void Builder::Build(ActorObj* pActor, const CaptainTakoEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setAudioSettingGroupPath(U"Enemy/CaptainTako/captain_tako.aase")
            .setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
        );

        // チャージ
        {
            pActor->attach<ChargeCtrl>();
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CaptainTako;

    class ViewBinder : public IVModelBinder<CaptainTakoVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<ChargeCtrl> m_charge;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<CaptainTakoVM> m_view;
    private:
        CaptainTakoVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime())
                .setChargeRate(m_charge->getRate())
                .setMotion(m_motion->get<Motion>())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<CaptainTakoVM>())
        {}
    };
}
