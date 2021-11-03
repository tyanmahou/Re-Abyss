#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Common/VModel.hpp>
#include <abyss/components/UI/BossHPBar/Main.hpp>

#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>
namespace
{
    class ViewBinder;
}
namespace abyss::UI::BossHPBar
{
    void Builder::Build(UIObj* pUi, Actor::ActorObj* pActor)
    {
        pUi->setFilter(Filter::Game | Filter::Event);

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
            pUi->attach<VModel>()
                ->setBinder<ViewBinder>(pUi);
        }
    };
}

namespace
{
    using namespace abyss;
    using namespace abyss::UI;
    using namespace abyss::UI::BossHPBar;

    class ViewBinder final : public IVModelBinder<BossHPBarVM>
    {
    public:
        ViewBinder(UIObj* pUi) :
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
        UIObj* m_pUi = nullptr;
        Ref<HPGaugeCtrl> m_hpGauge;

        std::unique_ptr<BossHPBarVM> m_view;
    };
}
