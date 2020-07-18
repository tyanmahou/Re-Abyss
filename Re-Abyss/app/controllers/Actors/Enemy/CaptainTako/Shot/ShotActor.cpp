#include "ShotActor.hpp"
#include <abyss/models/Actors/Enemy/CaptainTako/Shot/State/BaseState.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/ShotParam.hpp>

#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>
#include <abyss/models/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/Shot/DrawModel.hpp>

namespace abyss::CaptainTako::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward)
    {
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        {
            (m_body = this->attach<BodyModel>(this))
                ->setPos(pos)
                .setForward(forward)
                .noneResistanced()
                .setVelocityX(forward * ShotParam::Base::Speed)
                ;

            this->attach<BodyUpdaterModel>(this);
        }
        {
            this->attach<DeadOnHItReceiverModel>(this);
        }
        {
            this->attach<OutRoomCheckerModel>(this)
                ->setColFunc([this] {return this->getCollider(); });
        }
        {
            this->attach<AudioSourceModel>(this)
                ->load(U"Enemy/CaptainTako/captain_tako.aase");
        }
        {
            this->attach<DeadCheckerModel>(this);
        }
        {
            this->attach<DrawModel>(this);
        }
        {
            this->attach<StateModel>(this)
                ->changeState<BaseState>()
                ;
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
}
