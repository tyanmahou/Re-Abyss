#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    /// <summary>
    /// 描画
    /// </summary>
    class Drawer :
        public IComponent,
        public IDraw
    {
    public:
        Drawer(DecorObj* pObj);

        void onStart() override;

        void onDraw() const override;
    private:
        DecorObj* m_pObj;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Decor::General::SchoolOfFish::Drawer>
    {
        using Base = Decor::IDraw;
    };
}
