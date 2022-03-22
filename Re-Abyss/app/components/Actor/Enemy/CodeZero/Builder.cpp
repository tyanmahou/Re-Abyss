#include <abyss/components/Actor/Enemy/CodeZero/Builder.hpp>

#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BehaviorTest.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/DeadCallback.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Head/HeadVM.hpp>

namespace
{
    class ViewBinder;
    class ViewBinderHead;
}
namespace abyss::Actor::Enemy::CodeZero
{
    void Builder::Build(ActorObj* pActor, const CodeZeroEntity& entity)
    {
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setBodySize(Vec2{680, 480})
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableMapCollider(false)
            .setIsEnableDeadCallback(false)
            .setIsEnableBreathing(false)
            .setIsEnableItemDrop(false)
            .setIsAutoDestroy(false)
            .setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
        );

        // Body調整
        {
            pActor->find<Actor::Body>()->noneResistanced();
        }
        // パーツ制御
        Ref<ILocator> headLocator;
        {
            auto head = pActor->attach<HeadCtrl>(pActor);
            headLocator = RefCast<ILocator>(head);
            pActor->attach<PartsCtrl>(pActor);
        }
        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add<Col::CircleCollider>(pActor, headLocator)
                ->setRadius(Param::Head::ColRadius);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Receiver>(pActor);
        }
        // 行動パターン
        {
            pActor->attach<BehaviorCtrl>(pActor)
                ->setSequence(BehaviorSequence::Root)
                ;

#if ABYSS_DEBUG
            using std::placeholders::_1;
            pActor->attach<BehaviorTest>(pActor)
                ->setWaitAction(Behavior::WaitPursuitHands)
                .registAction(U"LeftAttack", Behavior::LeftAttack)
                .registAction(U"RightAttack", Behavior::RightAttack)
                .registAction(U"BothAttack", Behavior::BothAttack)
                .registAction(U"ChangeHandsPhase1", std::bind(Behavior::ChangeHandsPhase1, _1, false))
                .registAction(U"ChangeHandsPhase2", std::bind(Behavior::ChangeHandsPhase2, _1, false))
                .registAction(U"ChargeShot", Behavior::ChargeShot)
                .registAction(U"RollingAttack", std::bind(Behavior::RollingAttack, _1, false))
                .registAction(U"RollingAttack-R", std::bind(Behavior::RollingAttack, _1, true))
                .registAction(U"Phase2", Behavior::Phase2)
                .registAction(U"Phase3", Behavior::Phase3)
                .registAction(U"Appear", Behavior::Appear)
                .registAction(U"Angry", Behavior::Angry)
                .registAction(U"Dead", Behavior::Dead)
                ;
#endif
        }
        // プロキシ
        {
            pActor->attach<CodeZeroProxy>(pActor);
        }
        // 死亡時制御
        {
            pActor->attach<DeadCallback>(pActor);
        }
        // 描画制御
        {
            pActor->find<VModel>()->setOrder(DrawOrder::World::MostBack);

            pActor->attach<VModelSub<1>>()
                ->setBinder<ViewBinderHead>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;

    using abyss::Actor::Enemy::CodeZero::Body::BodyVM;

    class ViewBinder : public IVModelBinder<BodyVM>
    {
    private:
        BodyVM* bind() const final
        {
            return &m_view->setPos(m_body->getPos());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Actor::Body>();
        }
    public:
        ViewBinder(Actor::ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<BodyVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Actor::Body> m_body;
        std::unique_ptr<BodyVM> m_view;
    };

    class ViewBinderHead : public IVModelBinder<Head::HeadVM>
    {
    private:
        Head::HeadVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_head->getPos())
                .setLook(m_head->getLook())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        void setup(Executer executer) final
        {
        }
        void onStart() final
        {
            m_head = m_pActor->find<HeadCtrl>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
        }
    public:
        ViewBinderHead(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<Head::HeadVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<HeadCtrl> m_head;
        Ref<ColorCtrl> m_colorCtrl;
        std::unique_ptr<Head::HeadVM> m_view;
    };
}