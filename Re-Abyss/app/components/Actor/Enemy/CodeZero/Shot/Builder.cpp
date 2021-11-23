#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>

#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/ScaleCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/MainCollider.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/WaitState.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Shot/ShotVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
    {
        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(parent->find<Body>()->getPos())
                .noneResistanced();

            pActor->attach<BodyUpdater>(pActor);
        }
        // スケール制御
        {
            pActor->attach<ScaleCtrl>()
                ->set(0.0);
        }
        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add<MainCollider>(pActor);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Mover>(pActor)
                .attach<Col::Attacker>(pActor, 1)
                .attach<Col::Receiver>(pActor);
        }
        // 状態
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<WaitState>()
                ;
        }
        // 親制御
        {
            pActor->attach<ParentCtrl>(parent);
        }
        // 描画設定
        {
            pActor->attach<VModel>()
                ->setBinder<ViewBinder>(pActor);
        }
    }
}
namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Shot;

    class ViewBinder : public IVModelBinder<ShotVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ScaleCtrl> m_scale;
        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setScale(m_scale->get())
                .setIsCharge(m_scale->get() < 1.0)
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_scale = m_pActor->find<ScaleCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}