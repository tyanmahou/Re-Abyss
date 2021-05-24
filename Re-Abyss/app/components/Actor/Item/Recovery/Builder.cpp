#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

#include <abyss/components/Actor/Item/CommonBuilder.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>

#include <abyss/views/Actor/Item/Recovery/RecoveryVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Item::Recovery
{
    void Builder::Build(ActorObj* pActor, const RecoveryEntity& entity)
    {
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
        );

        // View
        {
            pActor->attach<ViewCtrl<RecoveryVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Item::Recovery;

    class ViewBinder : public ViewCtrl<RecoveryVM>::IBinder
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<RecoveryVM> m_view;
    private:
        RecoveryVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<RecoveryVM>())
        {}
    };
}