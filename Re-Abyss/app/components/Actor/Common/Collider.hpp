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
        using container_type = s3d::Array<std::shared_ptr<Col::ICollider>>;
        using const_iterator = container_type::const_iterator;
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

        template<class Type>
        Ref<Type> main() const requires std::derived_from<Type, Col::ICollider>
        {
            return RefCast<Type>(this->get(0));
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

        const_iterator begin() const
        {
            return m_colliders.begin();
        }
        const_iterator end() const
        {
            return m_colliders.end();
        }
        bool empty() const
        {
            return m_colliders.empty();
        }
        size_t size() const
        {
            return m_colliders.size();
        }

    private:
        container_type m_colliders;
    };
}