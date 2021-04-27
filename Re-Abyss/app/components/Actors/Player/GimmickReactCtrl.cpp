#include "GimmickReactCtrl.hpp"
#include "IGimmickReacter.hpp"

#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>

#include <abyss/components/Actors/Commons/StateCtrl.hpp>

namespace abyss::Actor::Player
{
   GimmickReactCtrl::GimmickReactCtrl(ActorObj* pActor):
       m_pActor(pActor)
    {}

   void GimmickReactCtrl::setup(Executer executer)
   {
       executer.on<IPostUpdate>().addAfter<StateCtrl>();
   }

   void GimmickReactCtrl::onPostUpdate()
   {
       for (auto&& reacter : m_pActor->getModule<World>()->finds<IGimmickReacter>()) {
           reacter->onGimmickReact(m_pActor);
       }
   }
}
