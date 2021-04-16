#pragma once

#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::decor
{
    class DecorInfo;
}
namespace abyss::decor::Map
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
    struct ComponentTree<decor::Map::MapDraw>
    {
        using Base = decor::IDraw;
    };
}