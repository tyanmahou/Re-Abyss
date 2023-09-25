#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>

namespace abyss::UI::DevPortal::TaskBoard
{
    class TaskBoardView;

    class TaskBoard final :
        public IComponent,
        public IDraw
    {
    public:
        TaskBoard(UIObj* pUi);
        ~TaskBoard();

        void onStart();
    public:
        void onDraw()const override;

    private:
        UIObj* m_pUi;
        Project* m_project;
        std::unique_ptr<Layout::Window::Window> m_window;
        std::unique_ptr<TaskBoardView> m_view;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::DevPortal::TaskBoard::TaskBoard>
    {
        using Base = MultiComponents<
            UI::IDraw
        >;
    };
}
#endif
