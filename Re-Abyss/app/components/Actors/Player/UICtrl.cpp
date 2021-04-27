#include "UICtrl.hpp"

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/UI/DyingEffect/Builder.hpp>
#include <abyss/components/UI/PlayerInfo/Builder.hpp>

namespace abyss::Actor::Player
{
    UICtrl::UICtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void UICtrl::onStart()
    {
        if (auto* ui = m_pActor->getModule<UIs>()) {
            ui->create<UI::PlayerInfo::Builder>(m_pActor);
            ui->create<UI::DyingEffect::Builder>(m_pActor);
        }
    }
}
