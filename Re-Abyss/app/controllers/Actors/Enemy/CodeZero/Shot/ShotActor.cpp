#include "ShotActor.hpp"

#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Shot/DrawModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Shot/State/WaitState.hpp>

#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>
namespace abyss::CodeZero::Shot
{
    ShotActor::ShotActor(CodeZeroActor* parent)
    {
        {
            this->attach<ParentCtrlModel>(parent);
        }
        {
            this->attach<StateModel>(this)
                ->changeState<WaitState>()
            ;
        }
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        {
            (m_scale = this->attach<ScaleModel>())
                ->set(0.0);
        }
        {
            (m_body = this->attach<BodyModel>(this))
                ->initPos(parent->getPos())
                .noneResistanced();

            this->attach<BodyUpdaterModel>(this);
        }
        {
            this->attach<DrawModel>(this);
        }
    }

    CShape ShotActor::getCollider() const
    {
        return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius * m_scale->get());
    }
    bool ShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }
}
