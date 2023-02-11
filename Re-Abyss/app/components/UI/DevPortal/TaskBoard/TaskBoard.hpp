#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>

#include <abyss/modules/Devs/Project/TaskBoard.hpp>

namespace abyss::UI::DevPortal
{
    class TaskBoard final :
        public IComponent,
        public IDraw
    {
    public:
        TaskBoard(UIObj* pUi);
    public:
        void onDraw()const override;
    private:
        UIObj* m_pUi;
        Devs::Project::TaskBoard m_task;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::DevPortal::TaskBoard>
    {
        using Base = MultiComponents<
            UI::IDraw
        >;
    };
}
#endif
