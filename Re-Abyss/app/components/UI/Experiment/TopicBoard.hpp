#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>

namespace abyss::UI::Experiment
{
    class TopicBoard final :
        public IComponent,
        public IDraw
    {
    public:
        TopicBoard(UIObj* pUi);
        ~TopicBoard();
    public:
        void onDraw()const override;
    private:
        UIObj* m_pUi;
        std::unique_ptr<Layout::Window::Window> m_window;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::Experiment::TopicBoard>
    {
        using Base = MultiComponents<
            UI::IDraw
        >;
    };
}
#endif
