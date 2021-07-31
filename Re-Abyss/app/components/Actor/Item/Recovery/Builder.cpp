#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

#include <abyss/components/Actor/Item/CommonBuilder.hpp>
#include <abyss/components/Actor/Item/Recovery/ItemReactor.hpp>
#include <abyss/components/Actor/Item/LifeSpan.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Commons/CustomDraw.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ShakeCtrl.hpp>

#include <abyss/params/Actor/Item/Recovery/Param.hpp>
#include <abyss/views/Actor/Item/Recovery/RecoveryVM.hpp>
#include <Siv3D.hpp>

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
        Build(pActor, entity.pos, entity.kind, entity.id);
    }
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, RecoveryKind kind)
    {
        Build(pActor, pos, kind, s3d::none);
    }
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, RecoveryKind kind, const s3d::Optional<s3d::uint32>& objId)
    {
        auto setting = ::GetSetting(kind);

        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(pos)
            .setBodySize(setting.size)
            .setBodyPivot(s3d::Vec2{ 0, 20.0 - setting.size.y / 2.0 })
            .setAudioSettingGroupPath(U"Item/Recovery/recovery.aase")
        );

        {
            pActor->attach<ItemReactor>(pActor, kind, objId);
        }
        {
            pActor->attach<ShakeCtrl>(pActor);
        }
        if (!objId) {
            // 直接生成の場合は時間制限で消える
            pActor->attach<LifeSpan>(pActor)->setLifeSpan(10.0);
        }
        // View
        {
            pActor->attach<ViewCtrl<RecoveryVM>>()
                ->createBinder<ViewBinder>(pActor, kind, setting);

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
            auto time = m_pActor->getDrawTimeSec();
            double alpha = 1.0;
            if (m_lifeSpan && m_lifeSpan->isWarn()) {
                auto rest = m_lifeSpan->restTimeSec();
                alpha = 0.2 + 0.8 * s3d::Periodic::Triangle0_1( (9.0 - (3.0 - rest) * ( 3.0 - rest)) / 3.0, time);
            }
            return &m_view
                ->setTime(time)
                .setPos(m_body->getPos() + m_shake->getShakeOffset())
                .setAlpha(alpha)
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_shake = m_pActor->find<ShakeCtrl>();
            m_lifeSpan = m_pActor->find<LifeSpan>();
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
        Ref<LifeSpan> m_lifeSpan;

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