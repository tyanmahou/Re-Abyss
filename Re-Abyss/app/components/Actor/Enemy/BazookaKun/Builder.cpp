#include <abyss/components/Actor/Enemy/BazookaKun/Builder.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/TargetCtrl.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/State/WaitState.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>
#include <abyss/views/Actor/Enemy/BazookaKun/BazookaKunVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::BazookaKun
{
    void Builder::Build(ActorObj* pActor, const BazookaKunEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            //.setBodyPivot(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            //.setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/BazookaKun/BazookaKun.aase")
            .setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
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
                ;
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::BazookaKun;

    class ViewBinder : public IVModelBinder<BazookaKunVM>
    {
    private:
        BazookaKunVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setIsMirrored(m_target->isMirrored())
                .setIsFlipped(m_target->isFlipped())
                .setRotate(m_target->rotate())
                .setBazookaRotate(s3d::Math::Lerp(0, 45, s3d::Periodic::Sine0_1(2s)))
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_target = m_pActor->find<TargetCtrl>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<BazookaKunVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<TargetCtrl> m_target;
        Ref<ColorCtrl> m_colorCtrl;

        std::unique_ptr<BazookaKunVM> m_view;
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
