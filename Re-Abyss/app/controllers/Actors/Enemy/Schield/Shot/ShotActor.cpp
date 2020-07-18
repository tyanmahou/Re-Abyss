#include <abyss/models/Actors/Enemy/Schield/Shot/State/BaseState.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>

#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/params/Actors/Enemy/Schield/ShotParam.hpp>

namespace abyss::Schield::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir) :
        m_view(std::make_shared<ShotVM>())
    {
        {
            this->attach<OldStateModel<ShotActor>>(this)
                ->add<BaseState>(State::Base);
        }
        {
            (m_body = this->attach<BodyModel>(this))
                ->initPos(pos)
                .noneResistanced()
                .setVelocity(dir.normalized() * ShotParam::Base::Speed);

        }
        {
            auto collider = this->attach<CustomColliderModel>(this);
            collider->setColFunc([this] {
                return this->getCollider();
            });
            collider->setLayer(LayerGroup::Enemy);
        }
        {
            this->attach<DeadOnHItReceiverModel>(this);
        }
        {
            this->attach<DeadCheckerModel>(this);
        }
        m_power = 1;
    }
    CShape ShotActor::getCollider() const
    {
        return this->getColliderCircle();
    }
    s3d::Circle ShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius);
    }

    bool ShotActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this)) ||
            visitor.visit(static_cast<IActor&>(*this));
    }

    ShotVM* ShotActor::getBindedView() const
    {
        return &m_view->setTime(this->getDrawTimeSec())
            .setPos(m_body->getPos());
    }
}
