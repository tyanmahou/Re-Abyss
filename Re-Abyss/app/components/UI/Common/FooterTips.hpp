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
        FooterTips(UIObj* pUi);

        FooterTips& setTips(const s3d::String& tips)
        {
            m_tips = tips;
            return *this;
        }
    public:
        void onDraw() const override;
    private:
        UIObj* m_pUi;
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
