#include "Builder.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>

#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/Colliders/CircleCollider.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/RotateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/HandProxy.h>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/HandCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/PursuitState.hpp>

#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>
namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void Builder::Build(IActor* pActor, IActor* parent, HandKind kind)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{});

        const auto forward = kind == HandKind::Left ? Forward::Left : Forward::Right;

        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(parent->find<Body>()->getPos() + s3d::Vec2{ forward * -110, 90 })
                .noneResistanced();
            pActor->attach<BodyUpdater>(pActor);
        }
        // 衝突
        {
            pActor->attach<CollisionCtrl>(pActor)
                ->setLayer(LayerGroup::Enemy);

            pActor->attach<CircleCollider>(pActor)
                ->setRadius(HandParam::Base::ColRadius);
        }
        // 回転制御
        {
            pActor->attach<RotateCtrl>();
        }
        // ハンド制御
        {
            pActor->attach<HandCtrl>();
            pActor->attach<KindCtrl>(kind);
        }
        // 親監視
        {
            pActor->attach<ParentCtrl>(parent);
        }
        // 状態
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<PursuitState>();
        }

        // AttackerData
        {
            pActor->attach<AttackerData>(1);
        }
        // 描画制御
        {
            pActor->attach<ViewCtrl<HandVM>>()
                ->createBinder<ViewBinder>(pActor, forward);
        }
        // プロキシ
        {
            pActor->attach<HandProxy>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Hand;

    class ViewBinder : public ViewCtrl<HandVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<RotateCtrl> m_rotate;
        std::unique_ptr<HandVM> m_view;
    private:
        HandVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setRotate(m_rotate->getRotate())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_rotate = m_pActor->find<RotateCtrl>();
        }
    public:
        ViewBinder(IActor* pActor, Forward forward) :
            m_pActor(pActor),
            m_view(std::make_unique<HandVM>(forward))
        {}
    };
}