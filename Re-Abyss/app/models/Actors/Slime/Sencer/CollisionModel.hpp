#pragma once
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>

namespace abyss::Slime::Sencer
{
    class CollisionModel : public ICollisionCallbackModel
    {
    private:
        bool m_onCollision = false;

    public:
        bool isOnCollision()const
        {
            return m_onCollision;
        }
        void onReflesh() override
        {
            m_onCollision = false;
        }
        void onCollisionStay(IActor* col) override;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Slime::Sencer::CollisionModel>
    {
        using Base = ICollisionCallbackModel;
    };
}