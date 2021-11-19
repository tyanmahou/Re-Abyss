#include "World.hpp"
#include <abyss/modules/Manager/Manager.hpp>

namespace abyss
{
    World::World()
    {}
    World::~World()
    {}
    void World::setManager(Manager* pManager)
    {
        m_pManager = pManager;
    }
    void World::init()
    {
        this->flush();
    }
    void World::flush()
    {
        m_actorsHolder.flush();
    }
    void World::updateDeltaTime(double dt)
    {
        m_actorsHolder.updateDeltaTime(dt);
    }
    void World::update()
    {
        m_actorsHolder.preUpdate();
        m_actorsHolder.update();
        m_actorsHolder.postUpdate();
    }

    void World::move()
    {
        m_actorsHolder.move();
    }

    void World::prePhysics()
    {
        m_actorsHolder.prePhysics();
    }

    void World::postPhysics()
    {
        // 地形判定
        m_actorsHolder.postPhysics();
    }

    void World::preCollision()
    {
        m_actorsHolder.preCollision();
    }

    void World::postCollision()
    {
        m_actorsHolder.postCollision();
    }

    void World::lastUpdate()
    {
        m_actorsHolder.lastUpdate();
    }

    void World::cleanUp()
    {
        m_actorsHolder.erase();
    }

    void World::onCheckIn()
    {
        m_actorsHolder.onCheckIn(Actor::FlipBuffer(m_bufferLayer));
    }

    void World::onCheckOut()
    {
        m_bufferLayer = Actor::FlipBuffer(m_bufferLayer);
        m_actorsHolder.onCheckOut(Actor::FlipBuffer(m_bufferLayer));
    }

    void World::draw() const
    {
        m_actorsHolder.draw();
    }

    std::shared_ptr<Actor::ActorObj> World::create()
    {
        auto obj = std::make_shared<Actor::ActorObj>();
        this->regist(obj);
        return obj;
    }

    void World::regist(const std::shared_ptr<Actor::ActorObj>& pActor)
    {
        pActor->setManager(m_pManager);
        pActor->setBufferLayer(m_bufferLayer);
        m_actorsHolder.pushActor(pActor);
    }
}
