#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Home/Top/Mode.hpp>
#include <abyss/components/UI/Home/Top/ModeUpdater.hpp>
#include <abyss/components/UI/Common/FooterTips.hpp>

#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

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
        void onStart() override;
        void onUpdate() override;
        void onDraw() const override;
    private:
        Coro::Fiber<> onUpdateAysnc();

        Coro::Fiber<> onSeek();
        Coro::Fiber<> onGuild();
        Coro::Fiber<> onMaint();
        Coro::Fiber<> onMemory();
        Coro::Fiber<> onCollect();
        Coro::Fiber<> onOption();

        void updateTips();
    private:
        UIObj* m_pUi;

        Mode m_mode = Mode::Seek;
        ModeUpdater m_modeUpdater;
        s3d::HashTable<Mode, bool> m_modeLocked;
        Ref<FooterTips> m_tips;
        double m_time = 0;
        TimeLite::Timer m_inAnime{0.5};

        std::unique_ptr<TopView> m_view;

        Coro::FiberHolder<> m_fiber;
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
