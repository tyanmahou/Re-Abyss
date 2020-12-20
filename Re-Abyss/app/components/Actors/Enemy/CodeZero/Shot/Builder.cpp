#include "Builder.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/ScaleCtrl.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Shot/State/WaitState.hpp>


namespace
{
    class Collider;
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void Builder::Build(IActor* pActor, IActor* parent)
    {
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{});

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
            pActor->attach<CollisionCtrl>(pActor)
                ->setLayer(LayerGroup::Enemy);

            pActor->attach<CustomCollider>()
                ->setImpl<Collider>(pActor);
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
        // 攻撃データ
        {
            pActor->attach<AttackerData>(1);
        }
        // 受け身データ
        {
            pActor->attach<ReceiverData>();
        }
        // 描画設定
        {
            pActor->attach<ViewCtrl<ShotVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
    }
}
namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Shot;

    class ViewBinder : public ViewCtrl<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ScaleCtrl> m_scale;
        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setScale(m_scale->get());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_scale = m_pActor->find<ScaleCtrl>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };

    class Collider : public Actor::CustomCollider::IImpl
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ScaleCtrl> m_scale;
    private:
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_scale = m_pActor->find<ScaleCtrl>();
        }
        CShape getCollider() const final
        {
            return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius * m_scale->get());
        }
    public:
        Collider(IActor* pActor) :
            m_pActor(pActor)
        {}
        ~Collider()
        {}
    };
}