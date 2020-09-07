#include "HeadActor.hpp"
#include <abyss/components/Actors/Enemy/CodeZero/Head/State/BaseState.hpp>

#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/HeadModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/DamageModel.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>
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
        // 親情報
        {
            m_parent = this->attach<ParentCtrlModel>(parent);
        }
        // 頭制御
        {
            m_head = this->attach<HeadModel>(this);
        }
        // 状態
        {
            this->attach<StateModel>(this)
                ->changeState<BaseState>()
                ;
        }
        // 当たり判定
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });

            this->attach<DamageModel>(this);
        }
        // 描画
        {
            this->attach<ViewModel<HeadVM>>()
                ->createBinder<ViewBinder>(this);
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
    bool HeadActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Receiver&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Head;

    class ViewBinder : public abyss::ViewModel<HeadVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<HeadModel> m_head;
        Ref<HPModel> m_hp;
        std::unique_ptr<HeadVM> m_view;
    private:
        HeadVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_head->getPos())
                .setForward(m_head->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup() final
        {
            m_head = m_pActor->find<HeadModel>();
            m_hp = m_pActor->find<ParentCtrlModel>()->getHp();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<HeadVM>())
        {}
    };
}