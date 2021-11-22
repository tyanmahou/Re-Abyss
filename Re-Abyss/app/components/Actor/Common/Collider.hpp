#pragma once
#include <concepts>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
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
        Ref<Type> add(Args&&... args) requires std::constructible_from<Type, Args...>
        {
            auto ret = std::make_shared<Type>(std::forward<Args>(args)...);
            this->add(ret);
            return ret;
        }

        Ref<Col::ICollider> add(const std::shared_ptr<Col::ICollider>& collider);
        Ref<Col::ICollider> add(const std::function<CShape()>& func);

        const s3d::Array<std::shared_ptr<Col::ICollider>>& getColliders() const
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

        Ref<Col::ICollider> main() const
        {
            return this->get(0);
        }
        Ref<Col::ICollider> get(size_t index) const
        {
            if (size() <= index) {
                return nullptr;
            }
            return m_colliders[index];
        }
    private:
        s3d::Array<std::shared_ptr<Col::ICollider>> m_colliders;
    };
}