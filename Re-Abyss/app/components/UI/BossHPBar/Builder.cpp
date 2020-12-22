#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/components/UI/BossHPBar/Main.hpp>

#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>
namespace
{
    class ViewBinder;
}
namespace abyss::ui::BossHPBar
{
    void Builder::Build(IUserInterface* pUi, Actor::IActor* pActor)
    {
        // メイン制御
        {
            pUi->attach<Main>(pUi);
        }
        // HPゲージ制御
        {
            pUi->attach<HPGaugeCtrl>(pActor);
        }
        // ビュー制御
        {
            pUi->attach<ViewCtrl<BossHPBarVM>>()
                ->createBinder<ViewBinder>(pUi);
        }
    };
}

namespace
{
    using namespace abyss;
    using namespace abyss::ui;
    using namespace abyss::ui::BossHPBar;

    class ViewBinder final : public ViewCtrl<BossHPBarVM>::IBinder
    {
    public:
        ViewBinder(IUserInterface* pUi) :
            m_pUi(pUi),
            m_view(std::make_unique<BossHPBarVM>())
        {}
    private:
        BossHPBarVM* bind() const override
        {
            return &m_view
                ->setHp(m_hpGauge->getHp())
                .setMaxHp(m_hpGauge->getMaxHp())
                ;
        }
        void onStart() override
        {
            m_hpGauge = m_pUi->find<HPGaugeCtrl>();
        }
    private:
        IUserInterface* m_pUi = nullptr;
        Ref<HPGaugeCtrl> m_hpGauge;

        std::unique_ptr<BossHPBarVM> m_view;
    };
}
