#include "UICtrl.hpp"

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/components/UI/DyingEffect/Builder.hpp>
#include <abyss/components/UI/PlayerInfo/Builder.hpp>

namespace abyss::Actor::Player
{
    UICtrl::UICtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void UICtrl::onStart()
    {
        if (auto* ui = m_pActor->getModule<UI>()) {
            ui->create<ui::PlayerInfo::Builder>(m_pActor);
            ui->create<ui::DyingEffect::Builder>(m_pActor);
        }
    }
}
