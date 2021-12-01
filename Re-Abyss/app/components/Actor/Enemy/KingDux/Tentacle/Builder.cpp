#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Tentacle/TentacleVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc)
    {
        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(parent->find<Body>()->getPos() + desc.offset)
                .noneResistanced();

            pActor->attach<BodyUpdater>(pActor);
        }
        // 回転
        {
            pActor->attach<RotateCtrl>();
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
            m_parentDamage(parent->find<DamageCtrl>()),
            m_view(std::make_unique<TentacleVM>())
        {}
    private:
        TentacleVM* bind() const final
        {
            bool isInvincibleTime = false;
            if (m_parentDamage) {
                isInvincibleTime = m_parentDamage->isInInvincibleTime();
            }
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setRotate(m_rotate->getRotate())
                .setIsDamaging(isInvincibleTime)
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_rotate = m_pActor->find<RotateCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<DamageCtrl> m_parentDamage;

        Ref<Body> m_body;
        Ref<RotateCtrl> m_rotate;

        std::unique_ptr<TentacleVM> m_view;
    };
}