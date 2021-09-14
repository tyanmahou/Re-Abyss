#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Common/ICollider.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 汎用当たり判定
    /// </summary>
    class CustomCollider : 
        public IComponent,
        public ICollider
    {
    public:
        class IImpl
        {
        public:
            virtual ~IImpl() = default;
            virtual void setup([[maybe_unused]]Executer executer) {}
            virtual void onStart() {}
            virtual CShape getCollider() const = 0;
        };
    private:
        std::shared_ptr<IImpl> m_pImpl;
        bool m_isActive = true;
    public:
        void setup(Executer executer)override;
        void onStart()override;

        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }
        CustomCollider& setImpl(const std::shared_ptr<IImpl>& impl);

        template<class Impl, class... Args>
        CustomCollider& setImpl(Args&&... args)
        {
            return setImpl(std::make_shared<Impl>(std::forward<Args>(args)...));
        }

        CustomCollider& setColFunc(const std::function<CShape()>& func);

        CShape getCollider() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::CustomCollider>
    {
        using Base = Actor::ICollider;
    };
}