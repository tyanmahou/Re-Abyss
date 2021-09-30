#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

#include <abyss/components/Actor/Common/ReceiverData.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/Colliders/CircleCollider.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Head/HeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Head/DamageCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Head/State/BaseState.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Head/HeadVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
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
            pActor->attach<VModel>()
                ->setBinder<ViewBinder>(pActor);
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

    class ViewBinder : public IVModelBinder<HeadVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<HeadCtrl> m_head;
        Ref<HP> m_hp;
        std::unique_ptr<HeadVM> m_view;
    private:
        HeadVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_head->getPos())
                .setForward(m_head->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup(Executer executer) final
        {
            executer.on<IComponent>().addAfter<ParentCtrl>();
        }
        void onStart() final
        {
            m_head = m_pActor->find<HeadCtrl>();
            m_hp = m_pActor->find<ParentCtrl>()->getHp();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<HeadVM>())
        {}
    };
}