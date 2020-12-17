#include "ShotActor.hpp"

#include <abyss/components/Actors/Enemy/Schield/Shot/State/BaseState.hpp>

#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>

#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/params/Actors/Enemy/Schield/ShotParam.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::Schield::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir)
    {
        m_tag = Tag::Enemy{} | Tag::Attacker{};
        {
            (m_body = this->attach<Body>(this))
                ->initPos(pos)
                .noneResistanced()
                .setVelocity(dir.normalized() * ShotParam::Base::Speed);

            this->attach<BodyUpdater>(this);
        }
        {
            this->attach<CollisionCtrl>(this)->setLayer(LayerGroup::Enemy);
            auto collider = this->attach<CustomCollider>();
            collider->setColFunc([this] {
                return this->getCollider();
            });
        }
        {
            this->attach<MapCollider>(this, false);
        }
        {
            this->attach<DeadOnHItReceiver>(this);
        }
        {
            this->attach<OutRoomChecker>(this)
                ->setColFunc([this] {return this->getCollider(); });
        }
        {
            this->attach<DeadChecker>(this);
        }
        {
            this->attach<ViewCtrl<ShotVM>>()
                ->createBinder<ViewBinder>(this);
        }
        {
            this->attach<StateCtrl>(this)
                ->changeState<BaseState>();
        }
        {
            this->attach<AttackerData>(1);
        }
    }
    CShape ShotActor::getCollider() const
    {
        return this->getColliderCircle();
    }
    s3d::Circle ShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::Schield;
    using namespace abyss::Actor::Enemy::Schield::Shot;

    class ViewBinder : public ViewCtrl<ShotVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}