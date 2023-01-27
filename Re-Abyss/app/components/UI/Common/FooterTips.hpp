#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <Siv3D/String.hpp>

namespace abyss::UI
{
    class FooterTips :
        public IComponent,
        public IDraw
    {
    public:
        FooterTips(const s3d::String& tips);
        void onDraw() const override;
        s3d::String m_tips;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::FooterTips>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}