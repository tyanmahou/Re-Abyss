#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>

namespace abyss::UI::Header
{
    class Main :
        public IComponent,
        public IDraw
    {

    public:
        Main(UIObj* pUi);

        void onStart() override;

        void onDraw() const override;
    private:
        UIObj* m_pUi;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Header::Main>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}