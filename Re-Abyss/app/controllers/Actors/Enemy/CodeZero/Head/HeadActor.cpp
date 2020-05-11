#include <abyss/models/Actors/CodeZero/Head/State/BaseState.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/views/Actors/CodeZero/Head/HeadVM.hpp>

namespace abyss::CodeZero::Head
{
    HeadActor::HeadActor(CodeZeroActor* parent) :
        m_view(std::make_shared<HeadVM>())
    {
        {
            m_parent = this->attach<ParentCtrlModel>(parent);
        }
        {
            m_head = this->attach<HeadModel>(this);
        }
        {
            this->attach<StateModel<HeadActor>>(this)
                ->add<BaseState>(State::Base)
                ;
        }
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
    }
    s3d::Vec2 HeadActor::getPos() const
    {
        return m_head->getPos();
    }

    CShape HeadActor::getCollider() const
    {
        return s3d::Circle(this->getPos() + s3d::Vec2{0, 10}, Param::Head::ColRadius);
    }
    bool HeadActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Receiver&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }
    HeadVM* HeadActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(m_head->getForward())
            .setIsDamaging(m_parent->getHp()->isInInvincibleTime());
    }
}
