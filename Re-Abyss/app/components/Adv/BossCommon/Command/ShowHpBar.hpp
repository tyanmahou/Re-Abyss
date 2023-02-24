#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/modules/UI/base/Filter.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Audio.hpp>

namespace abyss::UI::BossHPBar
{
    class HPGaugeCtrl;
}
namespace abyss::Adv::BossCommon
{
    class ShowHpBar :
        public ICommand
    {
    public:
        ShowHpBar(AdvObj* pObj);

        void onStart() override;
        void onEnd() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
        UI::Filter m_prevUiFilter;

        s3d::Audio m_chargeSe;

        Ref<UI::BossHPBar::HPGaugeCtrl> m_hpGauge;
    };
}
