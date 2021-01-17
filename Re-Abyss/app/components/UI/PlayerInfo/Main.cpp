#include "Main.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/views/UI/PlayerInfo/PlayerInfoExVM.hpp>
#include <abyss/params/UI/PlayerInfo/Param.hpp>

namespace abyss::ui::PlayerInfo
{
    Main::Main(IUserInterface* pUi, Actor::IActor* pActor):
        m_pUi(pUi),
        m_pActor(pActor),
        m_view(std::make_unique<PlayerInfoExVM>())
    {}

    void Main::onStart()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
    }

    void Main::onUpdate()
    {
    }

    void Main::onDraw() const
    {
        m_view
            ->setFace(U"default")
            .setOoparts(OopartsType::Xto)
            .setHp(m_hpModel->getHp())
            .setMaxHp(m_hpModel->getMaxHp())
            .setPos(Param::Main::DrawPos)
            .draw()
            ;
    }

}
