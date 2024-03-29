#include <abyss/components/UI/BossHPBar/Builder.hpp>

#include <abyss/components/UI/Common/VModel.hpp>
#include <abyss/components/UI/BossHPBar/Main.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>
namespace
{
    class Presenter;
}
namespace abyss::UI::BossHPBar
{
    void Builder::Build(UIObj* pUi, Actor::ActorObj* pActor)
    {
        Builder::Build(pUi, pActor->find<Actor::HP>(), pActor->find<Actor::DamageCtrl>());
    }
    void Builder::Build(UIObj* pUi, Ref<Actor::HP> hp, Ref<Actor::DamageCtrl> damage)
    {
        pUi->setFilter(Filter::Game | Filter::Event);

        // メイン制御
        {
            pUi->attach<Main>(pUi);
        }
        // HPゲージ制御
        {
            pUi->attach<HPGaugeCtrl>(pUi, hp, damage);
        }
        // ビュー制御
        {
            pUi->attach<VModel>()
                ->setPresenter<Presenter>(pUi);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::UI;
    using namespace abyss::UI::BossHPBar;

    class Presenter final : public IVModelPresenter<BossHPBarVM>
    {
    public:
        Presenter(UIObj* pUi) :
            m_pUi(pUi),
            m_view(std::make_unique<BossHPBarVM>())
        {}
    private:
        BossHPBarVM* bind() const override
        {
            return &m_view
                ->setHp(m_hpGauge->getHp())
                .setHpComboBuffer(m_hpGauge->getHpComboBuffer())
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
