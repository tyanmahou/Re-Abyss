#include "ShotActor.hpp"

#include <abyss/models/Actors/Enemy/Schield/Shot/State/BaseState.hpp>

#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>
#include <abyss/models/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>

#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/params/Actors/Enemy/Schield/ShotParam.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Schield::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir)
    {
        {
            (m_body = this->attach<BodyModel>(this))
                ->initPos(pos)
                .noneResistanced()
                .setVelocity(dir.normalized() * ShotParam::Base::Speed);

            this->attach<BodyUpdaterModel>(this);
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
            this->attach<OutRoomCheckerModel>(this)
                ->setColFunc([this] {return this->getCollider(); });
        }
        {
            this->attach<DeadCheckerModel>(this);
        }
        {
            this->attach<ViewModel<ShotVM>>()
                ->createBinder<ViewBinder>(this);
        }
        {
            this->attach<StateModel>(this)
                ->changeState<BaseState>();
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
}

namespace
{
    using namespace abyss;
    using namespace abyss::Schield;
    using namespace abyss::Schield::Shot;

    class ViewBinder : public ViewModel<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;

        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos());
        }
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}