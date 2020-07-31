#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>

namespace abyss
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

        CustomColliderModel& setImpl(std::unique_ptr<IImpl>&& impl);

        CustomColliderModel& setColFunc(const std::function<CShape()>& func);

        CShape getCollider() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CustomColliderModel>
    {
        using Base = IColliderModel;
    };
}