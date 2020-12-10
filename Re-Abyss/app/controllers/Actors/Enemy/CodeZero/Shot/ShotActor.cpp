#include "ShotActor.hpp"

#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Shot/State/WaitState.hpp>

#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/ScaleCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

namespace
{
    class ViewBinder;
    class Collider;
}
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    ShotActor::ShotActor(IActor* parent)
    {
        m_tag = Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{};
        {
            this->attach<ParentCtrl>(parent);
        }
        {
            this->attach<StateCtrl>(this)
                ->changeState<WaitState>()
            ;
        }
        {
            auto col = this->attach<CustomCollider>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setImpl<Collider>(this);
        }
        {
            this->attach<ScaleCtrl>()
                ->set(0.0);
        }
        {
            this->attach<Body>(this)
                ->initPos(parent->find<Body>()->getPos())
                .noneResistanced();

            this->attach<BodyUpdater>(this);
        }
        {
            this->attach<ViewCtrl<ShotVM>>()
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
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Shot;

    class ViewBinder : public ViewCtrl<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ScaleCtrl> m_scale;
        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setScale(m_scale->get());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_scale = m_pActor->find<ScaleCtrl>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };

    class Collider : public Actor::CustomCollider::IImpl
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ScaleCtrl> m_scale;
    private:
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_scale = m_pActor->find<ScaleCtrl>();
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

