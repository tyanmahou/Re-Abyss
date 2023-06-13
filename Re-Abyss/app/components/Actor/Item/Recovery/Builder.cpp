#include <abyss/components/Actor/Item/Recovery/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

#include <abyss/components/Actor/Item/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Item/CommonBuilder.hpp>
#include <abyss/components/Actor/Item/Recovery/ItemReactor.hpp>
#include <abyss/components/Actor/Item/LifeSpan.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>

#include <abyss/params/Actor/Item/Recovery/Param.hpp>
#include <abyss/views/Actor/Item/Recovery/RecoveryVM.hpp>
#include <Siv3D.hpp>

namespace
{
    class Presenter;
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
            .setDeployId(objId)
            .setInitPos(pos)
            .setBodySize(setting.size)
            .setBodyPivot(s3d::Vec2{ 0, 20.0 - setting.size.y / 2.0 })
        );

        {
            pActor->attach<ItemReactor>(pActor, kind);
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
            pActor->attach<VModel>()
                ->setPresenter<Presenter>(pActor, kind, setting);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Item::Recovery;

    class Presenter : public IVModelPresenter<RecoveryVM>
    {
    private:
        RecoveryVM* bind() const final
        {
            auto time = m_pActor->getTimeSec();
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
        Presenter(ActorObj* pActor, RecoveryKind kind, const Setting& setting) :
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
}
namespace abyss::Actor::Item
{
    template struct BuilderFromEntity<ItemType::Recovery>;
    template<>
    void BuilderFromEntity<ItemType::Recovery>::Build(ActorObj* pActor, const ItemEntity& entity)
    {
        Recovery::Builder::Build(pActor, static_cast<const RecoveryEntity&>(entity));
    }
}
