#include "ShotActor.hpp"
#include <abyss/components/Actors/Enemy/CaptainTako/Shot/State/BaseState.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/ShotParam.hpp>

#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward)
    {
        {
            auto col = this->attach<CustomCollider>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
            col->setTag(Collision::Tag::Enemy{} | Collision::Tag::Attacker{});
        }
        {
            (m_body = this->attach<Body>(this))
                ->setPos(pos)
                .setForward(forward)
                .noneResistanced()
                .setVelocityX(forward * ShotParam::Base::Speed)
                ;

            this->attach<BodyUpdater>(this);
        }
        {
            this->attach<DeadOnHItReceiver>(this);
        }
        {
            this->attach<OutRoomChecker>(this)
                ->setColFunc([this] {return this->getCollider(); });
        }
        {
            this->attach<AudioSource>(this)
                ->load(U"Enemy/CaptainTako/captain_tako.aase");
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
                ->changeState<BaseState>()
                ;
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

    bool ShotActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this)) ||
            visitor.visit(static_cast<IActor&>(*this));
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CaptainTako;
    using namespace abyss::Actor::Enemy::CaptainTako::Shot;

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
                .setPos(m_body->getPos())
                .setForward(m_body->getForward());
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