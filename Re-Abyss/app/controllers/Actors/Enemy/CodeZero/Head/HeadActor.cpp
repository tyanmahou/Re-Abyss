#include "HeadActor.hpp"
#include <abyss/components/Actors/Enemy/CodeZero/Head/State/BaseState.hpp>

#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/HeadCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/DamageCtrl.hpp>

#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Head/HeadVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    HeadActor::HeadActor(IActor* parent)
    {
        m_tag = Tag::Enemy{} | Tag::Receiver{};
        // 親情報
        {
            m_parent = this->attach<ParentCtrl>(parent);
        }
        // 頭制御
        {
            m_head = this->attach<HeadCtrl>(this);
        }
        // 状態
        {
            this->attach<StateCtrl>(this)
                ->changeState<BaseState>()
                ;
        }
        // 当たり判定
        {
            this->attach<CollisionCtrl>(this)->setLayer(LayerGroup::Enemy);
            auto col = this->attach<CustomCollider>();
            col->setColFunc([this] {return this->getCollider(); });

            this->attach<DamageCtrl>(this);
        }
        // 描画
        {
            this->attach<ViewCtrl<HeadVM>>()
                ->createBinder<ViewBinder>(this);
        }
        {
            this->attach<ReceiverData>();
        }
    }
    s3d::Vec2 HeadActor::getPos() const
    {
        return m_head->getPos();
    }

    CShape HeadActor::getCollider() const
    {
        return s3d::Circle(this->getPos() + s3d::Vec2{0, 10}, Param::Head::ColRadius);
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