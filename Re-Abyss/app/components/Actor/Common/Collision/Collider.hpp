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
            return this->add(std::make_shared<Type>(std::forward<Args>(args)...));
        }

        Ref<ICollider> add(const std::shared_ptr<ICollider>& collider);
        Ref<ICollider> add(const std::function<CShape()>& func);

        const s3d::Array<std::shared_ptr<ICollider>>& getColliders() const
        {
            return m_colliders;
        }

        bool empty() const
        {
            return m_colliders.empty();
        }
        size_t size() const
        {
            return m_colliders.size();
        }

        Ref<ICollider> main() const
        {
            return this->get(0);
        }
        Ref<ICollider> get(size_t index) const
        {
            if (size() <= index) {
                return nullptr;
            }
            return m_colliders[index];
        }
    private:
        s3d::Array<std::shared_ptr<ICollider>> m_colliders;
    };
}