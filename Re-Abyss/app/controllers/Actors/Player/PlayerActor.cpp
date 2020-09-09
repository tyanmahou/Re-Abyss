#include "PlayerActor.hpp"
#include <abyss/components/Actors/Player/State/SwimState.hpp>

#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Player/OopartsCtrl.hpp>
#include <abyss/components/Actors/Player/RestartCtrl.hpp>
#include <abyss/components/Actors/Player/RoomMoveChecker.hpp>
#include <abyss/components/Actors/Player/UICtrl.hpp>
#include <abyss/components/Actors/Player/DebugCtrl.hpp>

#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/models/Actors/Commons/BreathingModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/FallChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/CameraFixPos.hpp>

#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

#include <abyss/controllers/Manager/Manager.hpp>


namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Player
{
    PlayerActor::PlayerActor()
    {
        this->m_isDontDestoryOnLoad = true;

        // Collider
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Player);
            col->setColFunc([this]() {
                return this->getCollider();
            });
        }
        // Map Collider
        {
            this->attach<MapCollider>(this);
        }
        // Body
        {
            (m_body = this->attach<BodyModel>(this))
                ->setSize(Param::Base::Size)
                .setForward(Forward::Right)
             ;
        }
        // HP
        {
            (m_hp = this->attach<HPModel>(this))
                ->initHp(Param::Base::Hp)
                .setInvincibleTime(Param::Base::InvincibleTime);
        }
        // State
        {
            this->attach<StateModel>(this)
                ->changeState<SwimState>()
                ;
        }
        // Charge
        {
            this->attach<ChargeCtrl>();
        }
        // Foot
        {
            this->attach<Foot>();
        }
        // AudioSource
        {
            this->attach<AudioSource>(this)
                ->load(U"Player/player.aase");
        }
        // AttackCtrl
        {
            this->attach<AttackCtrl>(this);
        }
        {
            this->attach<OopartsCtrl>(this);
        }
        {
            this->attach<BreathingModel>(this)
                ->setOffset(s3d::Vec2{0, -20});
        }
        // カメラによる座標調整
        {
            this->attach<CameraFixPos>(this);
        }
        // 落下死
        {
            this->attach<FallChecker>(this);
        }
        // 死亡チェック
        {
            this->attach<DeadChecker>(this)
                ->setIsAutoDestroy(false);

            this->attach<RestartCtrl>(this);
        }
        // 部屋移動の検知
        {
            this->attach<RoomMoveChecker>(this);
        }
        {
            this->attach<ViewModel<PlayerVM>>()
                ->createBinder<ViewBinder>(this);
        }
        // UI制御
        {
            this->attach<UICtrl>(this);
        }
#if ABYSS_DEBUG
        // デバッグ制御
        {
            this->attach<DebugCtrl>(this);
        }
#endif
        m_order = 10;
    }
    void PlayerActor::setPos(const s3d::Vec2& pos)
    {
        m_body->setPos(pos);
    }

    void PlayerActor::setForward(const Forward& forward)
    {
        m_body->setForward(forward);
    }

    Forward PlayerActor::getForward() const
    {
        return m_body->getForward();
    }

    const s3d::Vec2& PlayerActor::getPos() const
    {
        return m_body->getPos();
    }

    CShape PlayerActor::getCollider() const
    {
        return this->region();
    }

    s3d::RectF PlayerActor::region() const
    {
        return m_body->region();
    }
    bool PlayerActor::isDead() const
    {
        return m_hp->isDead();
    }
    bool PlayerActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor::Player;

    class ViewBinder : public ViewModel<PlayerVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
        Ref<ChargeCtrl> m_charge;
        Ref<AttackCtrl> m_attackCtrl;

        std::unique_ptr<PlayerVM> m_view;
    private:
        PlayerVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setVelocity(m_body->getVelocity())
                .setForward(m_body->getForward())
                .setCharge(m_charge->getCharge())
                .setIsAttacking(m_attackCtrl->isAttacking())
                .setIsDamaging(m_hp->isInInvincibleTime())
                .setManager(m_pActor->getManager())
                ;
        }
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_attackCtrl = m_pActor->find<AttackCtrl>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<PlayerVM>())
        {}
    };
}

