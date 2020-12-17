#include "CollisionCtrl.hpp"
#include <abyss/components/Actors/base/ICollider.hpp>

namespace abyss::Actor
{
    class CollisionCtrl::Result
    {
    private:
        s3d::Array<Ref<ICollision>> m_results;
    public:
        Result() = default;

        void add(const Ref<ICollision>& collision)
        {
            m_results.push_back(collision);
        }
        void onReflesh()
        {
            m_results.clear();
        }

        const s3d::Array<Ref<ICollision>>& getResults() const
        {
            return m_results;
        }
        s3d::Array<IActor*> getHitActors() const
        {
            s3d::Array<IActor*> ret;
            for (const auto& col : m_results) {
                if (col) {
                    ret.push_back(col->getActor());
                }
            }
            return ret;
        }
    };
    CollisionCtrl::CollisionCtrl(IActor* pActor):
        ICollision(pActor),
        m_result(std::make_unique<Result>())
    {}
    CollisionCtrl::~CollisionCtrl()
    {}
    void CollisionCtrl::setup(Depends depends)
    {
        depends.addAfter<ICollider>();
    }
    void CollisionCtrl::onStart()
    {
        m_collider = m_pActor->find<ICollider>();
    }
    CShape CollisionCtrl::getCollider() const
    {
        return m_collider->getCollider();
    }
    void CollisionCtrl::onPreCollision()
    {
        m_result->onReflesh();
    }

    void CollisionCtrl::onCollision(const Ref<ICollision>& other)
    {
        m_result->add(other);
    }
    const s3d::Array<Ref<ICollision>>& CollisionCtrl::getResults() const
    {
        return m_result->getResults();
    }
    s3d::Array<IActor*> CollisionCtrl::getHitActors() const
    {
        return m_result->getHitActors();
    }
}
