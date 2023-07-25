#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/modules/UI/base/Filter.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Audio.hpp>

namespace abyss::UI::BossArrival
{
    class Main;
}
namespace abyss::Adv::BossCommon
{
    class BossArrival :
        public ICommand
    {
    public:
        BossArrival(AdvObj* pObj);

        void onStart() override;
        void onEnd() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
        UI::Filter m_prevUiFilter;

        Ref<UI::BossArrival::Main> m_main;
    };
}
