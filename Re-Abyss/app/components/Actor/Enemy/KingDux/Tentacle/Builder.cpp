#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Tentacle/TentacleVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
    {
        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(parent->find<Body>()->getPos())
                .noneResistanced();

            pActor->attach<BodyUpdater>(pActor);
        }

        // 描画制御
        {
            pActor->attach<VModel>()
                ->setBinder<ViewBinder>(pActor, parent);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::KingDux;
    using namespace abyss::Actor::Enemy::KingDux::Tentacle;

    class ViewBinder : public IVModelBinder<TentacleVM>
    {
    public:
        ViewBinder(ActorObj* pActor, ActorObj* parent) :
            m_pActor(pActor),
            m_parent(parent),
            m_view(std::make_unique<TentacleVM>())
        {}
    private:
        TentacleVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setIsDamaging(m_parentDamage->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_parentDamage = m_parent->find<DamageCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        ActorObj* m_parent = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_parentDamage;

        std::unique_ptr<TentacleVM> m_view;
    };
}