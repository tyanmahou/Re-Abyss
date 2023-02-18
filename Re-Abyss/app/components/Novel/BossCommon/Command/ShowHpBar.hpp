#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>
#include <abyss/modules/UI/base/Filter.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Audio.hpp>

namespace abyss::UI::BossHPBar
{
    class HPGaugeCtrl;
}
namespace abyss::Novel::BossCommon
{
    class ShowHpBar :
        public ICommand
    {
    public:
        ShowHpBar(TalkObj* pTalk);

        void onStart() override;
        void onEnd() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        UI::Filter m_prevUiFilter;

        s3d::Audio m_chargeSe;

        Ref<UI::BossHPBar::HPGaugeCtrl> m_hpGauge;
    };
}
