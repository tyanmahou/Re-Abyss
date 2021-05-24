#include "GimmickReactCtrl.hpp"
#include "IGimmickReactor.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>

#include <abyss/components/Actor/Commons/StateCtrl.hpp>

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
       for (auto&& reacter : m_pActor->getModule<World>()->finds<IGimmickReactor>()) {
           reacter->onGimmickReact(m_pActor);
       }
   }
}
