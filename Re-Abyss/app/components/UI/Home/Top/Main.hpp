#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Home/Top/Mode.hpp>

namespace abyss::UI::Home::Top
{
    class TopView;

    class Main final :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(UIObj* pUi);
        ~Main();
    public:
        void onUpdate() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Mode m_mode = Mode::Seek;

        std::unique_ptr<TopView> m_view;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::Home::Top::Main>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}
