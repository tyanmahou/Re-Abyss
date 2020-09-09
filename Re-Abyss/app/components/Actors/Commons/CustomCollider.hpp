#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 汎用当たり判定
    /// </summary>
    class CustomCollider : 
        public IComponent,
        public IColliderModel
    {
    public:
        class IImpl
        {
        public:
            virtual ~IImpl() = default;

            virtual void setup() = 0;
            virtual CShape getCollider() const = 0;
        };
    private:
        std::unique_ptr<IImpl> m_pImpl;
    public:
        using IColliderModel::IColliderModel;

        void setup()override;
        CustomCollider& setImpl(std::unique_ptr<IImpl>&& impl);

        template<class Impl, class... Args>
        CustomCollider& setImpl(Args&&... args)
        {
            return setImpl(std::make_unique<Impl>(std::forward<Args>(args)...));
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
        using Base = IColliderModel;
    };
}