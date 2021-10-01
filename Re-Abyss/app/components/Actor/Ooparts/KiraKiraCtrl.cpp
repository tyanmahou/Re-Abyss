#include "KiraKiraCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Ooparts/PursuitCtrl.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/components/Effect/Actor/Ooparts/Common/KiraKira/Builder.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Ooparts
{
    KiraKiraCtrl::KiraKiraCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_intervalTimer(0.05)
    {}
    void KiraKiraCtrl::setup(Executer executer)
    {
        executer.on<IPreDraw>().addAfter<PursuitCtrl>();
    }
    void KiraKiraCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    void KiraKiraCtrl::onPreDraw()
    {
        using namespace Effect::Actor::Ooparts;
        m_intervalTimer.update(m_pActor->deltaTime()).each([&](double) {
            auto effects = m_pActor->getModule<Effects>();
            const auto& pos = m_body->getPos();
            if (RandomBool(0.7)) {
                effects->createWorldBack<KiraKira::Builder>(pos + RandomVec2({ -15, 15 }, { 0, 20 }));
            } else {
                effects->createWorldBack<KiraKira::Builder>(pos + RandomVec2(17), KiraKira::Type::Type2);
            }
        });
    }
}
