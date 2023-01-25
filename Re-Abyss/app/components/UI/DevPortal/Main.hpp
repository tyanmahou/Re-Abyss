#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>

namespace abyss::UI::DevPortal
{
    class Main final:
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        enum class Mode
        {
            GameStart,
            Experiment,
        };
    public:
        Main(UIObj* pUi);

    public:
        void onUpdate() override;
    public:
        void onDraw()const;
    private:
        UIObj* m_pUi;
        Mode m_mode = Mode::GameStart;
    };
}
#endif
