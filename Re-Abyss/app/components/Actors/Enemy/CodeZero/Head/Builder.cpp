#include "Builder.hpp"

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>

#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Commons/Colliders/CircleCollider.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/HeadCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/DamageCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/State/BaseState.hpp>

#include <abyss/views/Actors/Enemy/CodeZero/Head/HeadVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    void Builder::Build(IActor* pActor, IActor* parent)
    {
        pActor->setTag(Tag::Enemy{} | Tag::Receiver{});

        // 親情報
        {
            pActor->attach<ParentCtrl>(parent);
        }
        // 頭制御
        {
            pActor->attach<HeadCtrl>(pActor);
        }
        // 状態
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<BaseState>()
                ;
        }
        // 当たり判定
        {
            pActor->attach<CollisionCtrl>(pActor)
                ->setLayer(LayerGroup::Enemy);
            pActor->attach<CircleCollider>(pActor)
                ->setRadius(Param::Head::ColRadius);
        }
        // ダメージ
        {
            pActor->attach<DamageCtrl>(pActor);
        }
        // 描画
        {
            pActor->attach<ViewCtrl<HeadVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
        {
            pActor->attach<ReceiverData>();
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Head;

    class ViewBinder : public ViewCtrl<HeadVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<HeadCtrl> m_head;
        Ref<HP> m_hp;
        std::unique_ptr<HeadVM> m_view;
    private:
        HeadVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_head->getPos())
                .setForward(m_head->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup(Depends depend) final
        {
            depend.on<IComponent>().addAfter<ParentCtrl>();
        }
        void onStart() final
        {
            m_head = m_pActor->find<HeadCtrl>();
            m_hp = m_pActor->find<ParentCtrl>()->getHp();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<HeadVM>())
        {}
    };
}