#include "Builder.hpp"
#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/Phase1State.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero
{
    void Builder::Build(ActorObj* pActor, const CodeZeroEntity& entity)
    {
        pActor->setOrder(-99);

        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableMapCollider(false)
            .setIsEnableDamage(false)
            .setIsEnableDeadCallback(false)
            .setIsEnableBreathing(false)
            .setIsAutoDestroy(false)
            .setInitState<Phase1State>()
        );

        // Body調整
        {
            pActor->find<Actor::Body>()->noneResistanced();
        }
        // パーツ制御
        {
            pActor->attach<PartsCtrl>(pActor);
        }
        // 行動パターン
        {
            pActor->attach<BehaviorCtrl>(pActor);
        }
        // view
        {
            pActor->attach<ViewCtrl<Body::BodyVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
        // プロキシ
        {
            pActor->attach<CodeZeroProxy>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor::Enemy::CodeZero;

    class ViewBinder : public Actor::ViewCtrl<Body::BodyVM>::IBinder
    {
        Actor::ActorObj* m_pActor = nullptr;
        Ref<Actor::Body> m_body;
        std::unique_ptr<Body::BodyVM> m_view;
    private:
        Body::BodyVM* bind() const final
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
            m_view(std::make_unique<Body::BodyVM>())
        {}
    };
}