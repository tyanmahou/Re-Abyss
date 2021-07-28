#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

#include <abyss/components/Actor/Item/CommonBuilder.hpp>
#include <abyss/components/Actor/Item/Recovery/ItemReactor.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Commons/CustomDraw.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ShakeCtrl.hpp>

#include <abyss/params/Actor/Item/Recovery/Param.hpp>
#include <abyss/views/Actor/Item/Recovery/RecoveryVM.hpp>

namespace
{
    class ViewBinder;
    class Drawer;
}
namespace
{
    using namespace abyss::Actor::Item;
    using namespace abyss::Actor::Item::Recovery;

    Setting GetSetting(RecoveryKind kind)
    {
        switch (kind) 	{
        case RecoveryKind::Small:
            return Param::Small;
        case RecoveryKind::Middle:
            return Param::Middle;
        case RecoveryKind::Big :
            return Param::Big;
        default:
            break;
        }
        return Param::Small;
    }
}
namespace abyss::Actor::Item::Recovery
{
    void Builder::Build(ActorObj* pActor, const RecoveryEntity& entity)
    {
        auto setting = ::GetSetting(entity.kind);

        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setBodySize(setting.size)
            .setBodyPivot(s3d::Vec2{ 0, 20.0 - setting.size.y / 2.0 })
            .setAudioSettingGroupPath(U"Item/Recovery/recovery.aase")
        );

        {
            pActor->attach<ItemReactor>(pActor, entity.kind, entity.id);
        }
        {
            pActor->attach<ShakeCtrl>(pActor);
        }
        // View
        {
            pActor->attach<ViewCtrl<RecoveryVM>>()
                ->createBinder<ViewBinder>(pActor, entity.kind, setting);

            pActor->attach<CustomDraw>()
                ->setDrawer<Drawer>(pActor);
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
    private:
        RecoveryVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos() + m_shake->getShakeOffset());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_shake = m_pActor->find<ShakeCtrl>();
            m_view->setKind(m_kind);
        }
    public:
        ViewBinder(ActorObj* pActor, RecoveryKind kind, const Setting& setting) :
            m_pActor(pActor),
            m_kind(kind),
            m_view(std::make_unique<RecoveryVM>(setting))
        {}
    private:

        ActorObj* m_pActor = nullptr;
        RecoveryKind m_kind;
        Ref<Body> m_body;
        Ref<ShakeCtrl> m_shake;

        std::unique_ptr<RecoveryVM> m_view;
    };

    class Drawer : public CustomDraw::IImpl
    {
    public:
        Drawer(ActorObj* pActor):
            m_pActor(pActor)
        {}
        void onStart()
        {
            m_view = m_pActor->find<ViewCtrl<RecoveryVM>>();
        }
        void onDraw()const
        {
            (*m_view)->draw();
        }
    private:

        ActorObj* m_pActor = nullptr;
        Ref<ViewCtrl<RecoveryVM>> m_view;
    };
}