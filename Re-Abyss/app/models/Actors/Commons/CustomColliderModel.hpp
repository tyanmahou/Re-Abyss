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
    private:
        std::function<CShape()> m_getCol;
    public:
        using IColliderModel::IColliderModel;

        void setColFunc(std::function<CShape()> func)
        {
            m_getCol = func;
        }

        CShape getCollider() const override
        {
            if (m_getCol) {
                return m_getCol();
            }
            return s3d::none;
        }
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