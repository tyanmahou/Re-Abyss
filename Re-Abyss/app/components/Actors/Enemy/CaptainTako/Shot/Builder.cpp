#include "Builder.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/ShotParam.hpp>

#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/Colliders/CircleCollider.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Enemy/CaptainTako/Shot/State/BaseState.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    void Builder::Build(IActor* pActor, const s3d::Vec2& pos, Forward forward)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{});

        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(pos)
                .setForward(forward)
                .noneResistanced()
                .setVelocityX(forward * ShotParam::Base::Speed);

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
        // サウンド
        {
            pActor->attach<AudioSource>(pActor)
                ->load(U"Enemy/CaptainTako/captain_tako.aase");
        }
        // 描画制御
        {
            pActor->attach<ViewCtrl<ShotVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
        // 状態
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<BaseState>()
                ;
        }
        // 攻撃データ
        {
            pActor->attach<AttackerData>(1);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CaptainTako;
    using namespace abyss::Actor::Enemy::CaptainTako::Shot;

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
                .setPos(m_body->getPos())
                .setForward(m_body->getForward());
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