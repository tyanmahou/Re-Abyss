#include "ShotActor.hpp"

#include <abyss/components/Actors/Enemy/LaunShark/Shot/State/StartState.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/DamageCtrl.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/models/Actors/Commons/StateModel.hpp>

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
        // 回転
        {
            m_rotate = this->attach<RotateModel>();
            if (forward == Forward::Right) {
                m_rotate->setRotate(s3d::Math::Constants::Pi);
            }
        }
        // コライダー
        {
            auto col = this->attach<CustomCollider>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        // ボディ
        {
            (m_body = this->attach<BodyModel>(this))
                ->setPos(pos)
                .noneResistanced()
                .setSize(ShotParam::Base::Size);

            this->attach<BodyUpdaterModel>(this);
        }
        // HP
        {
            this->attach<HPModel>(this)
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
            this->attach<StateModel>(this)
                ->changeState<StartState>()
                ;
        }
        // 描画
        {
            this->attach<ViewModel<ShotVM>>()
                ->createBinder<ViewBinder>(this);
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
    bool ShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor::Enemy::LaunShark;
    using namespace abyss::Actor::Enemy::LaunShark::Shot;

    class ViewBinder : public ViewModel<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
        Ref<RotateModel> m_rotate;

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
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
            m_rotate = m_pActor->find<RotateModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}