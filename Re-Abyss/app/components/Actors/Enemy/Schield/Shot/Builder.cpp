#include "Builder.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>

#include <abyss/components/Actors/Enemy/Schield/Shot/State/BaseState.hpp>

#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/Colliders/CircleCollider.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>

#include <abyss/params/Actors/Enemy/Schield/ShotParam.hpp>
#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::Schield::Shot
{
    void Builder::Build(IActor* pActor, const s3d::Vec2& pos, const s3d::Vec2& dir)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{});

        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(pos)
                .noneResistanced()
                .setVelocity(dir.normalized() * ShotParam::Base::Speed);

            pActor->attach<BodyUpdater>(pActor);
        }
        // 衝突
        {
            pActor->attach<CollisionCtrl>(pActor)
                ->setLayer(LayerGroup::Enemy);
            pActor->attach<CircleCollider>(pActor)
                ->setRadius(ShotParam::Base::ColRadius);
        }
        // 地形衝突
        {
            pActor->attach<MapCollider>(pActor, false);
        }
        // ヒット死亡
        {
            pActor->attach<DeadOnHItReceiver>(pActor);
        }
        // ルーム外死亡
        {
            pActor->attach<OutRoomChecker>(pActor);
        }
        // 死亡チェック
        {
            pActor->attach<DeadChecker>(pActor);
        }
        // State
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<BaseState>();
        }
        // AttackerData
        {
            pActor->attach<AttackerData>(pActor, 1);
        }
        // 描画制御
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
    using namespace abyss::Actor::Enemy::Schield;
    using namespace abyss::Actor::Enemy::Schield::Shot;

    class ViewBinder : public ViewCtrl<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}