#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Commons/AttackerData.hpp>
#include <abyss/components/Actor/Commons/ReceiverData.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>
#include <abyss/components/Actor/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Actor/Commons/CustomCollider.hpp>
#include <abyss/components/Actor/Commons/DamageCtrl.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actor/Commons/DeadCheacker.hpp>
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

#include <abyss/components/Actor/Enemy/DamageCallback.hpp>
#include <abyss/components/Actor/Enemy/DeadCallback.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/Shot/State/StartState.hpp>

#include <Siv3D/MathConstants.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, Forward forward)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{});

        // Body
        {
            pActor->attach<Body>(pActor)
                ->setPos(pos)
                .noneResistanced()
                .setSize(ShotParam::Base::Size);
            pActor->attach<BodyUpdater>(pActor);
        }
        // 回転
        {
            auto rotate = pActor->attach<RotateCtrl>();
            if (forward == Forward::Right) {
                rotate->setRotate(s3d::Math::Constants::Pi);
            }
        }
        // HP
        {
            pActor->attach<HP>(pActor)
                ->initHp(ShotParam::Base::Hp)
                .setInvincibleTime(0.2);
        }
        // 音源
        {
            pActor->attach<AudioSource>(pActor)
                ->load(U"Enemy/LaunShark/shot.aase");
        }

        // 衝突
        {
            pActor->attach<CollisionCtrl>(pActor)
                ->setLayer(LayerGroup::Enemy);

            auto body = pActor->find<Body>();
            auto rotate = pActor->find<RotateCtrl>();
            pActor->attach<CustomCollider>()
                ->setColFunc([body, rotate]()->CShape {
                return body->region().rotated(rotate->getRotate());
            });
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
        // ダメージ
        {
            pActor->attach<DamageCtrl>(pActor);
            pActor->attach<Enemy::DeadCallback>(pActor);
            pActor->attach<Enemy::DamageCallback>(pActor);
        }
        // 死亡チェック
        {
            pActor->attach<DeadChecker>(pActor);
        }
        // State
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<StartState>();
        }
        // AttackerData
        {
            pActor->attach<AttackerData>(pActor, 1);
        }
        // ReceiverData
        {
            pActor->attach<ReceiverData>();
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
    using namespace abyss::Actor::Enemy::LaunShark;
    using namespace abyss::Actor::Enemy::LaunShark::Shot;

    class ViewBinder : public ViewCtrl<ShotVM>::IBinder
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<RotateCtrl> m_rotate;

        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setRotate(m_rotate->getRotate())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_rotate = m_pActor->find<RotateCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}