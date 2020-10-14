#include "PlayerActor.hpp"
#include <abyss/components/Actors/Player/State/SwimState.hpp>

#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Player/OopartsCtrl.hpp>
#include <abyss/components/Actors/Player/RestartCtrl.hpp>
#include <abyss/components/Actors/Player/RoomMoveChecker.hpp>
#include <abyss/components/Actors/Player/UICtrl.hpp>
#include <abyss/components/Actors/Player/DebugCtrl.hpp>

#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/BreathingCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/FallChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/CameraFixPos.hpp>
#include <abyss/components/Actors/Commons/LightCtrl.hpp>

#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/views/Actors/Ooparts/base/ActDrawCallbackView.hpp>

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
            auto col = this->attach<CustomCollider>(this);
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
            (m_body = this->attach<Body>(this))
                ->setSize(Param::Base::Size)
                .setForward(Forward::Right)
             ;
        }
        // HP
        {
            (m_hp = this->attach<HP>(this))
                ->initHp(Param::Base::Hp)
                .setInvincibleTime(Param::Base::InvincibleTime);
        }
        // State
        {
            this->attach<StateCtrl>(this)
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
            this->attach<BreathingCtrl>(this)
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
        // View
        {
            this->attach<ViewCtrl<PlayerVM>>()
                ->createBinder<ViewBinder>(this);
        }
        // Light
        {
            this->attach<LightCtrl>(this)
                ->setRadius(700.0);
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
    using namespace abyss::Actor;
    using namespace abyss::Actor::Player;

    class ViewBinder : public ViewCtrl<PlayerVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
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
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_attackCtrl = m_pActor->find<AttackCtrl>();

            auto xtoView = std::make_unique<XtoAtkVM>();
            xtoView->setCallback(std::make_unique <Ooparts::ActDrawCallbackView> (xtoView.get(), m_pActor->getManager()));
            m_view->setXtoAtkView(std::move(xtoView));
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<PlayerVM>())
        {}
    };
}

