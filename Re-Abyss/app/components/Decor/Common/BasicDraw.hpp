#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Decor/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Decor
{
    class DecorInfo;

    /// <summary>
    /// 基本描画
    /// </summary>
    class BasicDraw :
        public IComponent,
        public IDraw
    {
    public:
        BasicDraw(DecorObj* pObj);

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
    struct ComponentTree<Decor::BasicDraw>
    {
        using Base = Decor::IDraw;
    };
}