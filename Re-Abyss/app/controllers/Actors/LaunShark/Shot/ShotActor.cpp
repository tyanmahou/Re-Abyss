#include <abyss/models/Actors/LaunShark/Shot/State/WaitState.hpp>
#include <abyss/models/Actors/LaunShark/Shot/State/PursuitState.hpp>
#include <abyss/models/Actors/LaunShark/Shot/State/FiringedState.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>


#include <abyss/commons/LayerGroup.hpp>
#include <Siv3D/MathConstants.hpp>
#include <abyss/params/Actors/LaunShark/ShotParam.hpp>

namespace abyss::LaunShark::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward):
        m_view(std::make_shared<ShotVM>())
    {
        m_rotate = this->attach<RotateModel>();

        if (forward == Forward::Right) {
            m_rotate->setRotate(s3d::Math::Constants::Pi);
        }

        auto col = this->attach<CustomColliderModel>(this);
        col->setLayer(LayerGroup::Enemy);
        col->setColFunc([this] {return this->getCollider(); });
        (m_body = this->attach<BodyModel>(this))
            ->setPos(pos)
            .noneResistanced()
            .setSize(ShotParam::Base::Size);
        (m_hp = this->attach<HPModel>(this))
            ->setHp(ShotParam::Base::Hp).setInvincibleTime(0.2);

        this->attach<exp::StateModel<ShotActor>>(this)
            ->add<WaitState>(State::Wait)
            .add<PursuitState>(State::Pursuit)
            .add<FiringedState>(State::Firinged)
            ;

        this->attach<DamageModel>(this);
        this->attach<DeadOnHItReceiverModel>(this);
        this->attach<Enemy::DeadCallbackModel>(this);
    }
    void ShotActor::start()
    {    
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

    ShotVM* ShotActor::getBindedView() const
    {
        return &(*m_view)
            .setPos(m_body->getPos())
            .setRotate(m_rotate->getRotate())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
