#include "ShotActor.hpp"

#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Shot/State/WaitState.hpp>

#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

namespace
{
    class ViewBinder;
    class Collider;
}
namespace abyss::CodeZero::Shot
{
    ShotActor::ShotActor(IActor* parent)
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
            col->setImpl<Collider>(this);
        }
        {
            this->attach<ScaleModel>()
                ->set(0.0);
        }
        {
            this->attach<BodyModel>(this)
                ->initPos(parent->find<BodyModel>()->getPos())
                .noneResistanced();

            this->attach<BodyUpdaterModel>(this);
        }
        {
            this->attach<ViewModel<ShotVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }

    bool ShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }
}
namespace
{
    using namespace abyss;
    using namespace abyss::CodeZero;
    using namespace abyss::CodeZero::Shot;

    class ViewBinder : public ViewModel<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<ScaleModel> m_scale;
        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setScale(m_scale->get());
        }
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
            m_scale = m_pActor->find<ScaleModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };

    class Collider : public CustomColliderModel::IImpl
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<ScaleModel> m_scale;
    private:
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
            m_scale = m_pActor->find<ScaleModel>();
        }
        CShape getCollider() const final
        {
            return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius * m_scale->get());
        }
    public:
        Collider(IActor* pActor) :
            m_pActor(pActor)
        {}
        ~Collider()
        {}
    };
}

