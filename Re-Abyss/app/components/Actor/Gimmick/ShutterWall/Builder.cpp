#include <abyss/components/Actor/Gimmick/ShutterWall/Builder.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/ColorAnim/DamageColor.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/DamageCallback.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/MainCollider.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterCtrl.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>
#include <abyss/views/Actor/Gimmick/ShutterWall/ShutterWallVM.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Gimmick::ShutterWall
{
    void Builder::Build(ActorObj* pActor, const ShutterWallEntity& entity)
    {
        // 地形
        {
            pActor->attach<TerrainProxy>(pActor)
                ->setColDirection(ColDirection::All)
                .setRegion(ShutterUtil::RegionFromCenter(entity.pos))
                .setTag(Physics::Tag::Floor{})
                ;
        }
        // 座標
        {
            pActor->attach<Locator>()
                ->setPos(entity.pos)
                ;
        }
        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add<MainCollider>(pActor);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Gimmick)
                .attach<Col::Receiver>(pActor)
                ;
        }
        // ダメージ
        {
            pActor->attach<HP>(pActor)
                ->setHp(Param::Hp);

            pActor->attach<DamageCtrl>(pActor)
                ->setInvincibleTime(0.2);
            pActor->attach<DamageCallback> (pActor);
            pActor->attach<DeadChecker>(pActor);

            // 色制御
            pActor->attach<ColorCtrl>(pActor);
            pActor->attach<ColorAnim::DamageColor>(pActor);
        }
        // シャッター制御
        {
            pActor->attach<ShutterCtrl>(pActor);
        }
        // 描画
        {
            pActor->attach<VModel>()
                ->setBinder<ViewBinder>(pActor)
                ;
        }
        // 音源
        {
            pActor->attach<AudioSource>(pActor)
                ->load(U"Gimmick/ShutterWall/ShutterWall.aase");
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Gimmick;
    using namespace abyss::Actor::Gimmick::ShutterWall;

    class ViewBinder : public IVModelBinder<ShutterWallVM>
    {
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShutterWallVM>())
        {
        }

        void onStart() override
        {
            m_locator = m_pActor->find<Locator>();
            m_shutter = m_pActor->find<ShutterCtrl>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
        }
        ShutterWallVM* bind() const override
        {
            return &m_view
                ->setPos(m_locator->getPos())
                .setShutterRate(m_shutter->getShutterRate())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
    private:
        ActorObj* m_pActor;

        Ref<Locator> m_locator;
        Ref<ShutterCtrl> m_shutter;
        Ref<ColorCtrl> m_colorCtrl;
        std::unique_ptr<ShutterWallVM> m_view;
    };
}

namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::ShutterWall>;
    template<>
    void BuilderFromEntity<GimmickType::ShutterWall>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        ShutterWall::Builder::Build(pActor, static_cast<const ShutterWallEntity&>(entity));
    }
}
