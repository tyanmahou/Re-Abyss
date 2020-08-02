#include "PlayerActor.hpp"
#include <abyss/models/Actors/Player/State/SwimState.hpp>

#include <abyss/models/Actors/Player/AttackCtrlModel.hpp>
#include <abyss/models/Actors/Player/OopartsCtrlModel.hpp>
#include <abyss/models/Actors/Player/RestartCtrlModel.hpp>
#include <abyss/models/Actors/Player/RoomMoveCheckerModel.hpp>
#include <abyss/models/Actors/Player/DebugCtrlModel.hpp>

#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/BreathingModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Commons/FallCheckerModel.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>
#include <abyss/models/Actors/Commons/CameraFixPosModel.hpp>

#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

#include <abyss/controllers/Manager/Manager.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Ooparts/Xto/XtoActor.hpp>

#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/PlayerInfo/PlayerInfo.hpp>
#include <abyss/controllers/UI/DyingEffect/DyingEffect.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Player
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
            this->attach<MapColliderModel>(this);
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
            this->attach<ChargeModel>();
        }
        // Foot
        {
            this->attach<FootModel>();
        }
        // AudioSource
        {
            this->attach<AudioSourceModel>(this)
                ->load(U"Player/player.aase");
        }
        // AttackCtrl
        {
            this->attach<AttackCtrlModel>(this);
        }
        {
            this->attach<OopartsCtrlModel>(this);
        }
        {
            this->attach<BreathingModel>(this)
                ->setOffset(Vec2{0, -20});
        }
        // カメラによる座標調整
        {
            this->attach<CameraFixPosModel>(this);
        }
        // 落下死
        {
            this->attach<FallCheckerModel>(this);
        }
        // 死亡チェック
        {
            this->attach<DeadCheckerModel>(this)
                ->setIsAutoDestroy(false);

            this->attach<RestartCtrlModel>(this);
        }
        // 部屋移動の検知
        {
            this->attach<RoomMoveCheckerModel>(this);
        }
        {
            this->attach<ViewModel<PlayerVM>>()
                ->createBinder<ViewBinder>(this);
        }
#if ABYSS_DEBUG
        // デバッグ制御
        {
            this->attach<DebugCtrlModel>(this);
        }
#endif
        m_order = 10;
    }
    void PlayerActor::start()
    {
        m_pManager->set(this);
        // todo 切り替え可能に
        std::shared_ptr<Ooparts::OopartsActor> main = this->getModule<World>()->create<Ooparts::Xto::XtoActor>(this);
        this->find<OopartsCtrlModel>()->setMain(main);

        this->getModule<UI>()->create<ui::PlayerInfo>(this);
        this->getModule<UI>()->create<ui::DyingEffect>(this);
    }
    void PlayerActor::setPos(const Vec2& pos)
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

    const Vec2& PlayerActor::getPos() const
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
    using namespace abyss::Player;

    class ViewBinder : public ViewModel<PlayerVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
        Ref<ChargeModel> m_charge;
        Ref<AttackCtrlModel> m_attackCtrl;
    private:
        PlayerVM* bind(PlayerVM* view) const
        {
            return &view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setVelocity(m_body->getVelocity())
                .setForward(m_body->getForward())
                .setCharge(m_charge->getCharge())
                .setIsAttacking(m_attackCtrl->isAttacking())
                .setIsDamaging(m_hp->isInInvincibleTime())
                .setManager(m_pActor->getManager())
                ;
        }
        void setup() override
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
            m_charge = m_pActor->find<ChargeModel>();
            m_attackCtrl = m_pActor->find<AttackCtrlModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor)
        {}
    };
}

