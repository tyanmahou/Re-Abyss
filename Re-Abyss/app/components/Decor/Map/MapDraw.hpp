#pragma once

#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Decor
{
    class DecorInfo;
}
namespace abyss::Decor::Map
{
    /// <summary>
    /// 地形描画
    /// </summary>
    class MapDraw :
        public IComponent,
        public IDraw
    {
    public:
        MapDraw(DecorObj* pObj);

        void onStart() override;

        void onDraw() const override;
    private:
        DecorObj* m_pObj;
        Ref<DecorInfo> m_info;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Decor::Map::MapDraw>
    {
        using Base = Decor::IDraw;
    };
}