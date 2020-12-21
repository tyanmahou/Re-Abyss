#include "UICtrl.hpp"

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/modules/UI/PlayerInfo/PlayerInfo.hpp>
#include <abyss/modules/UI/DyingEffect/DyingEffect.hpp>

namespace abyss::Actor::Player
{
    UICtrl::UICtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void UICtrl::onStart()
    {
        if (auto* ui = m_pActor->getModule<UI>()) {
            ui->create<ui::PlayerInfo>(m_pActor);
            ui->create<ui::DyingEffect>(m_pActor);
        }
    }
}
