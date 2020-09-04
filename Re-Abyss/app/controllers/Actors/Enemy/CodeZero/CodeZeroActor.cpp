#include "CodeZeroActor.hpp"

#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/PartsModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase1State.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::CodeZero
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableMapCollider(false)
            .setIsEnableDamage(false)
            .setIsEnableDeadCallback(false)
            .setIsEnableBreathing(false)
            .setIsAutoDestroy(false)
            .setInitState<Phase1State>()
            .build();
        {
            m_hp->initHp(Param::Base::Hp);
        }
        {
            m_body->noneResistanced();
        }
        {
            m_parts = this->attach<PartsModel>(this);
        }
        {
            this->attach<PatternModel>(this);
        }
        // view
        {
            this->attach<ViewModel<Body::BodyVM>>()
                ->createBinder<ViewBinder>(this);
        }
        m_order = -99;
    }

    bool CodeZeroActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

    void CodeZeroActor::setActiveAll(bool active)
    {
        this->setActive(active);
        m_parts->setActive(active);
    }
}
namespace
{
    using namespace abyss;
    using namespace abyss::Actor::CodeZero;

    class ViewBinder : public ViewModel<Body::BodyVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        std::unique_ptr<Body::BodyVM> m_view;
    private:
        Body::BodyVM* bind() const final
        {
            return &m_view->setPos(m_body->getPos());
        }
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<Body::BodyVM>())
        {}
    };
}