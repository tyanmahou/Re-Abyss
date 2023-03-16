#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D/String.hpp>

namespace abyss::UI
{
    class FooterTips :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        FooterTips(UIObj* pUi);

        FooterTips& setTips(const s3d::String& tips)
        {
            m_tips = tips;
            m_timer.reset();
            return *this;
        }
    public:
        void onUpdate() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        s3d::String m_tips;
        TimeLite::Timer m_timer{ 1 / 3.0 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::FooterTips>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}
