#include <abyss/models/Actors/CodeZero/Shot/State/WaitState.hpp>
#include <abyss/models/Actors/CodeZero/Shot/State/PursuitState.hpp>
#include <abyss/models/Actors/CodeZero/Shot/State/PursuitEndState.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/commons/LayerGroup.hpp>
#include <abyss/views/Actors/CodeZero/Shot/ShotVM.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/ShotParam.hpp>
namespace abyss::CodeZero::Shot
{
    ShotActor::ShotActor(CodeZeroActor* parent):
        m_view(std::make_shared<ShotVM>())
    {
        {
            this->addComponent<ParentCtrlModel>(parent);
        }
        {
            this->addComponent<exp::StateModel<ShotActor>>(this)
                ->add<WaitState>(State::Wait)
                .add<PursuitState>(State::Pursuit)
                .add<PursuitEndState>(State::PursuitEnd)
            ;
        }
        {
            auto col = this->addComponent<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        {
            (m_scale = this->addComponent<ScaleModel>())
                ->set(0.0);
        }
        {
            (m_body = this->addComponent<BodyModel>())
                ->initPos(parent->getPos())
                .noneResistanced();
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

    ShotVM* ShotActor::getBindedView() const
    {
        return &m_view->setPos(m_body->getPos())
            .setScale(m_scale->get());
    }

}
