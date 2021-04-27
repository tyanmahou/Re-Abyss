#include "Main.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/views/UI/PlayerInfo/PlayerInfoExVM.hpp>
#include <abyss/params/UI/PlayerInfo/Param.hpp>

namespace abyss::UI::PlayerInfo
{
    Main::Main(UIObj* pUi, Actor::ActorObj* pActor):
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
