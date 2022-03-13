#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>

namespace abyss::Actor
{
    class TerrainProxy::Terrain final :
        public Physics::ITerrain
    {
    public:
        Terrain(ActorObj* pActor):
            m_pActor(pActor)
        {}

        void setId(s3d::uint64 id)
        {
            m_id = id;
        }
        s3d::uint64 id() const
        {
            return m_id;
        }
        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }
        bool isActive() const
        {
            return m_isActive && !m_isDestroyed && m_pActor->isActive();
        }

        void destroy()
        {
            m_isDestroyed = true;
        }

        bool isDestroyed() const override
        {
            return m_isDestroyed;
        }

        Physics::TerrainData& getData()
        {
            return m_data;
        }
        const Physics::TerrainData& getData() const
        {
            return m_data;
        }

    private:
        ActorObj* m_pActor;
        bool m_isActive = true;
        bool m_isDestroyed = false;
        Physics::TerrainData m_data;
        s3d::uint64 m_id;
    };
    TerrainProxy::TerrainProxy(ActorObj* pActor):
        m_pActor(pActor),
        m_terrain(std::make_shared<Terrain>(pActor))
    {}
    void TerrainProxy::setup([[maybe_unused]]Executer executer)
    {}
    void TerrainProxy::onStart()
    {
        // 地形登録
        m_pActor->getModule<PhysicsManager>()->regist(m_terrain);
    }
    void TerrainProxy::onEnd()
    {
        // 破棄
        m_terrain->destroy();
    }
    TerrainProxy& TerrainProxy::setColDirection(ColDirection col)
    {
        m_terrain->getData().col = col;
        return *this;
    }
    TerrainProxy& TerrainProxy::setRegion(const s3d::RectF& region)
    {
        m_terrain->getData().region = region;
        return *this;
    }
    TerrainProxy& TerrainProxy::setTag(const Physics::TagType& tag)
    {
        m_terrain->getData().tag = tag;
        return *this;
    }
    TerrainProxy& TerrainProxy::setExtData(std::shared_ptr<Physics::ITerrainExtData> data)
    {
        m_terrain->getData().extData = data;
        return *this;
    }
    TerrainProxy& TerrainProxy::setActive(bool isActive)
    {
        m_terrain->setActive(isActive);
        return *this;
    }
}
