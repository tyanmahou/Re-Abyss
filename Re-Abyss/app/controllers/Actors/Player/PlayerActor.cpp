#include <abyss/models/Actors/Player/State/SwimState.hpp>
#include <abyss/models/Actors/Player/State/LadderState.hpp>
#include <abyss/models/Actors/Player/State/DamageState.hpp>
#include <abyss/models/Actors/Player/AttackCtrlModel.hpp>
#include <abyss/models/Actors/Player/OopartsCtrlModel.hpp>


#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/BreathingModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Ooparts/Xto/XtoActor.hpp>

#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/DyingEffect/DyingEffect.hpp>

namespace abyss::Player
{
    PlayerActor::PlayerActor() :
        m_view(std::make_shared<PlayerVM>())
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
            (m_state = this->attach<StateModel<PlayerActor>>(this))
                ->add<SwimState>(State::Swim)
                .add<LadderState>(State::Ladder)
                .add<DamageState>(State::Damage)
            ;
        }
        // Charge
        {
            m_charge = this->attach<ChargeModel>();
        }
        // Foot
        {
            m_foot = this->attach<FootModel>();
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
        m_order = 10;
    }
    void PlayerActor::start()
    {
        m_pManager->set(this);
        // todo 切り替え可能に
        std::shared_ptr<Ooparts::OopartsActor> main = this->getModule<World>()->create<Ooparts::Xto::XtoActor>(this);
        this->find<OopartsCtrlModel>()->setMain(main);

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

    RectF PlayerActor::region() const
    {
        return m_body->region();
    }
    bool PlayerActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
    PlayerVM* PlayerActor::getBindedView() const
    {
        return &m_view->setTime(this->getDrawTimeSec())
            .setPos(this->getPos())
            .setVelocity(m_body->getVelocity())
            .setForward(m_body->getForward())
            .setCharge(m_charge->getCharge())
            .setIsAttacking(this->find<AttackCtrlModel>()->isAttacking())
            .setIsDamaging(m_hp->isInInvincibleTime())
            .setManager(m_pManager)
            ;
    }
    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}
