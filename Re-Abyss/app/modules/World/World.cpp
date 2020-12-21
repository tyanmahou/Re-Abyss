#include "World.hpp"

#include <abyss/models/Collision/CollisionModel.hpp>
#include <abyss/models/Collision/MapCollisionModel.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/components/Actors/base/ICollision.hpp>
#include <abyss/components/Actors/base/IPhysics.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>

#include <abyss/debugs/DebugManager/DebugManager.hpp>

namespace abyss
{
    World::World() :
        m_collision(std::make_unique<SimpleCollision>()),
        m_mapCollision(std::make_unique<SimpleMapCollision>())
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
        m_actorsHolder.update();
    }

    void World::move()
    {
        m_actorsHolder.move();
    }

    void World::physics()
    {
        // 地形判定
        m_actorsHolder.prePhysics();
        m_mapCollision->collisionAll(this->finds<Actor::IPhysics>(), this->finds<Actor::Terrain>());
        m_actorsHolder.lastPhysics();
    }

    void World::collision()
    {
        // アクター衝突
        m_actorsHolder.preCollision();
        m_collision->collisionAll(this->finds<Actor::ICollision>());
        m_actorsHolder.collisionReact();
    }

    void World::lastUpdate()
    {
        m_actorsHolder.lastUpdate();
    }

    void World::cleanUp()
    {
        m_actorsHolder.erase();
    }

    void World::reset()
    {
        m_actorsHolder.clear();
        m_collision->reset();
    }

    void World::draw() const
    {
        m_actorsHolder.draw();
#if ABYSS_DEBUG
        Debug::DebugManager::DrawColider(*this);
        Debug::DebugManager::DrawMapColider(*this);
#endif

    }

    std::shared_ptr<Actor::IActor> World::create()
    {
        auto obj = std::make_shared<Actor::IActor>();
        this->regist(obj);
        return obj;
    }

    void World::regist(const std::shared_ptr<Actor::IActor>& pActor)
    {
        pActor->setManager(m_pManager);
        m_actorsHolder.pushActor(pActor);
    }
}
