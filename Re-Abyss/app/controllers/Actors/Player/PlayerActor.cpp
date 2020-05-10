#include <abyss/models/Actors/Player/State/SwimState.hpp>
#include <abyss/models/Actors/Player/State/LadderState.hpp>
#include <abyss/models/Actors/Player/State/DamageState.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>

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
                ->setHp(Param::Base::Hp)
                .setInvincibleTime(Param::Base::InvincibleTime);
        }
        // State
        {
            (m_state = this->attach<exp::StateModel<PlayerActor>>(this))
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
        m_order = 10;
    }
    void PlayerActor::start()
    {
        m_pManager->set(this);
    }
    void PlayerActor::setPos(const Vec2& pos)
    {
        m_body->setPos(pos);
    }

    void PlayerActor::setForward(const Forward& forward)
    {
        m_body->setForward(forward);
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
        return &m_view->setPos(this->getPos())
            .setVelocity(m_body->getVelocity())
            .setForward(m_body->getForward())
            .setCharge(m_charge->getCharge())
            .setIsDamaging(m_hp->isInInvincibleTime())
            .setManager(m_pManager)
            ;
    }
    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}
