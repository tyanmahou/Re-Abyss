#include "UICtrl.hpp"

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/PlayerInfo/PlayerInfo.hpp>
#include <abyss/controllers/UI/DyingEffect/DyingEffect.hpp>

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
