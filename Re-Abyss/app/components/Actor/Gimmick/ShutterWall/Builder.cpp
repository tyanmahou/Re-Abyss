#include <abyss/components/Actor/Gimmick/ShutterWall/Builder.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
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
        {
            pActor->attach<TerrainProxy>(pActor)
                ->setColDirection(ColDirection::All)
                .setRegion(ShutterUtil::Region(entity.pos))
                ;
        }
        // 座標
        {
            pActor->attach<Locator>()
                ->setPos(entity.pos)
                ;
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
        }
        ShutterWallVM* bind() const override
        {
            return &m_view
                ->setPos(m_locator->getPos())
                .setShutterRate(m_shutter->getShutterRate())
                ;
        }
    private:
        ActorObj* m_pActor;

        Ref<Locator> m_locator;
        Ref<ShutterCtrl> m_shutter;
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
