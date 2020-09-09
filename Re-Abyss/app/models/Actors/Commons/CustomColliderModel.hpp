#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 汎用当たり判定
    /// </summary>
    class CustomColliderModel : 
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
        CustomColliderModel& setImpl(std::unique_ptr<IImpl>&& impl);

        template<class Impl, class... Args>
        CustomColliderModel& setImpl(Args&&... args)
        {
            return setImpl(std::make_unique<Impl>(std::forward<Args>(args)...));
        }

        CustomColliderModel& setColFunc(const std::function<CShape()>& func);

        CShape getCollider() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::CustomColliderModel>
    {
        using Base = IColliderModel;
    };
}