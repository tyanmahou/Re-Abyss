#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Common/Collision/Collider/ICollider.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Collision
{
    /// <summary>
    /// 当たり判定
    /// </summary>
    class Collider :
        public IComponent
    {
    public:
        void setup(Executer executer)override;
        void onStart()override;

        template<class Type, class ... Args>
        Ref<ICollider> add(Args&&... args)
        {
            return this->add(std::make_shared<Type>(std::forward<Args>(args)...);
        }

        Ref<ICollider> add(const std::shared_ptr<ICollider>& collider);
        Ref<ICollider> add(const std::function<CShape()>& func);
    private:
        s3d::Array<std::shared_ptr<ICollider>> m_colliders;
    };
}