#include <abyss/components/UI/PlayerInfo/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/views/UI/PlayerInfo/PlayerInfoExVM.hpp>
#include <abyss/params/UI/PlayerInfo/Param.hpp>

namespace abyss::UI::PlayerInfo
{
    Main::Main(UIObj* pUi, Actor::ActorObj* pActor):
        m_pUi(pUi),
        m_pActor(pActor),
        m_view(std::make_unique<PlayerInfoExVM>())
    {}
    Main::~Main()
    {}
    void Main::onStart()
    {
        m_hp = m_pActor->find<Actor::HP>();
        m_damage = m_pActor->find<Actor::DamageCtrl>();
    }

    void Main::onUpdate()
    {
    }

    void Main::onDraw() const
    {
        m_view
            ->setFace((m_damage->isInvincibleTime() || m_hp->isDead()) ? U"damage" : U"default")
            .setOoparts(OopartsType::Xto)
            .setHp(m_hp->getHp())
            .setMaxHp(m_hp->getMaxHp())
            .setPos(Param::Main::DrawPos)
            .draw()
            ;
    }

}
