#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Manager/Manager.hpp>

namespace abyss::Actor
{
    Actors::Actors()
    {}
    Actors::~Actors()
    {}
    void Actors::setManager(Manager* pManager)
    {
        m_pManager = pManager;
    }
    void Actors::init()
    {
        this->flush();
    }
    void Actors::flush()
    {
        m_actorsHolder.flush();
    }
    void Actors::updateDeltaTime(double dt)
    {
        m_actorsHolder.updateDeltaTime(dt);
    }
    void Actors::update()
    {
        m_actorsHolder.preUpdate();
        m_actorsHolder.update();
        m_actorsHolder.postUpdate();
    }

    void Actors::move()
    {
        m_actorsHolder.move();
    }

    void Actors::prePhysics()
    {
        m_actorsHolder.prePhysics();
    }

    void Actors::postPhysics()
    {
        // 地形判定
        m_actorsHolder.postPhysics();
    }

    void Actors::preCollision()
    {
        m_actorsHolder.preCollision();
    }

    void Actors::postCollision()
    {
        m_actorsHolder.postCollision();
    }

    void Actors::lastUpdate()
    {
        m_actorsHolder.lastUpdate();
    }

    void Actors::cleanUp()
    {
        m_actorsHolder.erase();
    }

    void Actors::onCheckIn()
    {
        m_actorsHolder.onCheckIn(Actor::FlipBuffer(m_bufferLayer));
    }

    void Actors::onCheckOut()
    {
        m_bufferLayer = Actor::FlipBuffer(m_bufferLayer);
        m_actorsHolder.onCheckOut(Actor::FlipBuffer(m_bufferLayer));
    }

    void Actors::draw() const
    {
        m_actorsHolder.draw();
    }

    std::shared_ptr<Actor::ActorObj> Actors::create()
    {
        auto obj = std::make_shared<Actor::ActorObj>();
        this->regist(obj);
        return obj;
    }

    void Actors::regist(const std::shared_ptr<Actor::ActorObj>& pActor)
    {
        pActor->setManager(m_pManager);
        pActor->setBufferLayer(m_bufferLayer);
        m_actorsHolder.pushActor(pActor);
    }
}
