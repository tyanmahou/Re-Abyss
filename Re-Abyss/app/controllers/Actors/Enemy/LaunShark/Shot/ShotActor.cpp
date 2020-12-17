#include "ShotActor.hpp"

#include <abyss/components/Actors/Enemy/LaunShark/Shot/State/StartState.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/DamageCtrl.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>

#include <abyss/components/Actors/Enemy/DamageCallback.hpp>
#include <abyss/components/Actors/Enemy/DeadCallback.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>
#include <Siv3D/MathConstants.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward)
    {
        m_tag = Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{};
        // 回転
        {
            m_rotate = this->attach<RotateCtrl>();
            if (forward == Forward::Right) {
                m_rotate->setRotate(s3d::Math::Constants::Pi);
            }
        }
        // コライダー
        {
            this->attach<CollisionCtrl>(this)->setLayer(LayerGroup::Enemy);
            auto col = this->attach<CustomCollider>();
            col->setColFunc([this] {return this->getCollider(); });
        }
        // 地形判定
        {
            this->attach<MapCollider>(this, false);
        }
        // ボディ
        {
            (m_body = this->attach<Body>(this))
                ->setPos(pos)
                .noneResistanced()
                .setSize(ShotParam::Base::Size);

            this->attach<BodyUpdater>(this);
        }
        // HP
        {
            this->attach<HP>(this)
                ->initHp(ShotParam::Base::Hp).setInvincibleTime(0.2);
        }
        // 音源
        {
            this->attach<AudioSource>(this)->load(U"Enemy/LaunShark/shot.aase");
        }
        // ダメージ
        {
            this->attach<DamageCtrl>(this);
            this->attach<Enemy::DeadCallback>(this);
        }
        // 死亡チェック
        {
            this->attach<DeadOnHItReceiver>(this);
            this->attach<Enemy::DamageCallback>(this);
            this->attach<DeadChecker>(this);
        }
        // 状態管理
        {
            this->attach<StateCtrl>(this)
                ->changeState<StartState>()
                ;
        }
        // 描画
        {
            this->attach<ViewCtrl<ShotVM>>()
                ->createBinder<ViewBinder>(this);
        }
        {
            this->attach<AttackerData>(1);
        }
        {
            this->attach<ReceiverData>();
        }
    }

    CShape ShotActor::getCollider() const
    {
        return this->getColliderQuad();
    }
    s3d::Quad ShotActor::getColliderQuad() const
    {
        return m_body->region().rotated(m_rotate->getRotate());
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
        IActor* m_pActor = nullptr;
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
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}