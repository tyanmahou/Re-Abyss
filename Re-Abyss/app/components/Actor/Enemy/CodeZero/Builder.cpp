#include <abyss/components/Actor/Enemy/CodeZero/Builder.hpp>

#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/Phase1State.hpp>

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
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableMapCollider(false)
            .setIsEnableDeadCallback(false)
            .setIsEnableBreathing(false)
            .setIsEnableItemDrop(false)
            .setIsAutoDestroy(false)
            .setInitState<Phase1State>()
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
            pActor->attach<BehaviorCtrl>(pActor);
        }
        // プロキシ
        {
            pActor->attach<CodeZeroProxy>(pActor);
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
        ActorObj* m_pActor = nullptr;
        Ref<Actor::Body> m_body;
        std::unique_ptr<BodyVM> m_view;
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
    };

    class ViewBinderHead : public IVModelBinder<Head::HeadVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<HeadCtrl> m_head;
        Ref<DamageCtrl> m_damage;
        std::unique_ptr<Head::HeadVM> m_view;
    private:
        Head::HeadVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_head->getPos())
                .setForward(m_head->getForward())
                .setIsDamaging(m_damage->isInInvincibleTime());
        }
        void setup(Executer executer) final
        {
        }
        void onStart() final
        {
            m_head = m_pActor->find<HeadCtrl>();
            m_damage = m_pActor->find<DamageCtrl>();
        }
    public:
        ViewBinderHead(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<Head::HeadVM>())
        {}
    };
}