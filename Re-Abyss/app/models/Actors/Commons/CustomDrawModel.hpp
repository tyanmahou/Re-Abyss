#pragma once
#include <functional>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>

namespace abyss
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    class CustomDrawModel :
        public IComponent,
        public IDrawModel
    {
    private:
        std::function<void()> m_drawer;
    public:
        CustomDrawModel& setDrawer(const std::function<void()>& drawer)
        {
            m_drawer = drawer;
            return *this;
        }
        void onDraw() const override
        {
            if (m_drawer) {
                m_drawer();
            }
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CustomDrawModel>
    {
        using Base = IDrawModel;
    };
}