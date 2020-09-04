#include "UICtrlModel.hpp"

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/PlayerInfo/PlayerInfo.hpp>
#include <abyss/controllers/UI/DyingEffect/DyingEffect.hpp>

namespace abyss::Actor::Player
{
    UICtrlModel::UICtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void UICtrlModel::onStart()
    {
        if (auto* ui = m_pActor->getModule<UI>()) {
            ui->create<ui::PlayerInfo>(m_pActor);
            ui->create<ui::DyingEffect>(m_pActor);
        }
    }
}
