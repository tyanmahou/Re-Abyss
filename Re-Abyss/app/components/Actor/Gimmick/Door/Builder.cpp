#include <abyss/components/Actor/Gimmick/Door/Builder.hpp>

#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actor/Gimmick/Door/GimmickReactor.hpp>

#include <abyss/views/Actor/Gimmick/Door/DoorVM.hpp>

namespace
{
    class Presenter;
}

namespace abyss::Actor::Gimmick::Door
{
    void Builder::Build(ActorObj* pActor, const DoorEntity& entity)
    {
        pActor->setDestoryTiming(DestoryTiming::CheckIn);

        // プロキシー
        auto proxy = pActor->attach<DoorProxy>(pActor, entity);

        // コライダー
        {
            pActor->attach<Collider>()
                ->add([proxy] {return proxy->getCollider(); });
        }

        // ギミック反応
        {
            pActor->attach<GimmickReactor>(pActor);
        }

        // 描画制御
        {
            pActor->attach<VModel>()
                ->setPresenter<Presenter>(pActor)
                .setLayer(DrawLayer::WorldBack);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Gimmick::Door;

    class Presenter : public IVModelPresenter<DoorVM>
    {
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<DoorVM>())
        {}

        void onStart() override
        {
            m_door = m_pActor->find<DoorProxy>();
        }
        DoorVM* bind() const override
        {
            return &m_view
                ->setPos(m_door->getPos())
                .setKind(m_door->getKind())
                .setTime(m_pActor->getTimeSec());
        }
    private:
        ActorObj* m_pActor;
        Ref<DoorProxy> m_door;

        std::unique_ptr<DoorVM> m_view;
    };
}
namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::Door>;
    template<>
    void BuilderFromEntity<GimmickType::Door>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        Door::Builder::Build(pActor, static_cast<const DoorEntity&>(entity));
    }
}
