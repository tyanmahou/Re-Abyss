#include <abyss/components/Actor/Enemy/BazookaKun/Builder.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/TargetCtrl.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/MainCollider.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>
#include <abyss/views/Actor/Enemy/BazookaKun/BazookaKunVM.hpp>

namespace
{
    class Presenter;
}

namespace abyss::Actor::Enemy::BazookaKun
{
    void Builder::Build(ActorObj* pActor, const BazookaKunEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setInitState<WaitState>()
            .setVModelPresenter<Presenter>(pActor, entity.footPos)
            .setIsEnableBreathing(false)
        );
        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
        {
            pActor->attach<TargetCtrl>(pActor)
                ->setIsMirrored(entity.isMirrored)
                .setIsFlipped(entity.isFlipped)
                .setRotate(entity.rotate)
                .setBazookaRotate(entity.bazookaRotate)
                .setIsFixBazooka(entity.isFixBazooka)
                ;
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::BazookaKun;

    class Presenter : public IVModelPresenter<BazookaKunVM>
    {
    private:
        BazookaKunVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_footPos /*m_body->getPos()*/)
                .setIsMirrored(m_target->isMirrored())
                .setIsFlipped(m_target->isFlipped())
                .setRotate(m_target->rotate())
                .setBazookaRotate(m_target->bazookaRotate())
                .setBazookaAnimRate(m_motion->animeTime())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_target = m_pActor->find<TargetCtrl>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        Presenter(ActorObj* pActor, Vec2 footPos) :
            m_pActor(pActor),
            m_view(std::make_unique<BazookaKunVM>()),
            m_footPos(footPos)
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<TargetCtrl> m_target;
        Ref<ColorCtrl> m_colorCtrl;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<BazookaKunVM> m_view;

        Vec2 m_footPos;
    };
}


namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::BazookaKun>;
    template<>
    void BuilderFromEntity<EnemyType::BazookaKun>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        BazookaKun::Builder::Build(pActor, static_cast<const BazookaKunEntity&>(entity));
    }
}
