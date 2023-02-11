#include <abyss/components/Actor/Enemy/CaptainTako/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Enemy/CaptainTakoEntity.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>

#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/State/WaitState.hpp>
#include <abyss/views/Actor/Enemy/CaptainTako/CpatainTakoVM.hpp>

namespace
{
    class Presenter;
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
            .setAudioSettingGroupPath(U"Enemy/CaptainTako/CaptainTako.aase")
            .setInitState<WaitState>()
            .setVModelPresenter<Presenter>(pActor)
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

    class Presenter : public IVModelPresenter<CaptainTakoVM>
    {
    private:
        CaptainTakoVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setChargeRate(m_charge->getRate())
                .setMotion(m_motion->get<Motion>())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<CaptainTakoVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ColorCtrl> m_colorCtrl;
        Ref<ChargeCtrl> m_charge;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<CaptainTakoVM> m_view;
    };
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::CaptainTako>;
    template<>
    void BuilderFromEntity<EnemyType::CaptainTako>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        CaptainTako::Builder::Build(pActor, static_cast<const CaptainTakoEntity&>(entity));
    }
}
