#include <abyss/models/Actors/CaptainTako/Shot/State/BaseState.hpp>
#include <abyss/views/Actors/CaptainTako/Shot/ShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/CaptainTako/ShotParam.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>

namespace abyss::CaptainTako::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward):
        m_view(std::make_shared<ShotVM>())
    {
        {
            auto col = this->addComponent<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }

        {
            this->addComponent<exp::StateModel<ShotActor>>(this)
                ->add<BaseState>(State::Base)
                ;
        }
        {
            (m_body = this->addComponent<BodyModel>(this))
                ->setPos(pos)
                .setForward(forward)
                .noneResistanced()
                .setVelocityX(forward * ShotParam::Base::Speed)
                ;
        }
        {
            this->addComponent<DeadOnHItReceiverModel>(this);
        }
        m_power = 1;
    }

    void ShotActor::start()
    {
    
    }

    CShape ShotActor::getCollider() const
    {
        return this->getColliderCircle();
    }

    s3d::Circle ShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius);
    }

    bool ShotActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this)) ||
            visitor.visit(static_cast<IActor&>(*this));
    }

    ShotVM* ShotActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body->getPos())
            .setForward(m_body->getForward());
    }

}
