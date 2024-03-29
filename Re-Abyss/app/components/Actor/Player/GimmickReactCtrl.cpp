#include <abyss/components/Actor/Player/GimmickReactCtrl.hpp>
#include <abyss/components/Actor/Player/IGimmickReactor.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>

#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Player/PlayerUtil.hpp>

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
       if (PlayerUtil::IsDead(m_pActor)) {
           // 死んでたら無視
           return;
       }
       for (auto&& reacter : m_pActor->getModule<Actors>()->finds<IGimmickReactor>()) {
           reacter->onGimmickReact(m_pActor);
       }
   }
}
