#include <abyss/components/UI/DyingEffect/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>

#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/views/UI/DyingEffect/DyingEffectVM.hpp>

namespace abyss::UI::DyingEffect
{
    Main::Main(UIObj* pUi, Actor::ActorObj* pActor):
        m_pUi(pUi),
        m_pActor(pActor),
        m_view(std::make_unique<DyingEffectVM>())
    {}
    Main::~Main()
    {}
    void Main::onStart()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
        m_pUi->getModule<PostEffects>()
            ->getColorLayer()
            ->setColor(ColorF(1, 0, 0, 0.8));
    }

    void Main::onUpdate()
    {
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
        m_hp = static_cast<double>(m_hpModel->getHp());
    }


    void Main::onDraw() const
    {
        // ポストエフェクト設定
        {
            m_pUi->getModule<PostEffects>()
                ->getColorLayer()
                ->setIsValid(m_hp <= 0);
        }
        m_view
            ->setHp(m_hp)
            .setMaxHp(m_maxHp)
            .setTime(m_pUi->getModule<GlobalTime>()->time())
            .draw();
    }

}
