#include <abyss/components/Actor/Enemy/BazookaKun/Builder.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>
#include <abyss/views/Actor/Enemy/BazookaKun/BazookaKunVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::BazookaKun
{
    void Builder::Build(ActorObj* pActor, const BazookaKunEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            //.setBodyPivot(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            //.setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/BazookaKun/BazookaKun.aase")
            //.setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
        );
        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::BazookaKun;

    class ViewBinder : public IVModelBinder<BazookaKunVM>
    {
    private:
        BazookaKunVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<BazookaKunVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<BazookaKunVM> m_view;
    };
}


namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::BazookaKun>;
    template<>
    void BuilderFromEntity<EnemyType::BazookaKun>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        BazookaKun::Builder::Build(pActor, static_cast<const BazookaKunEntity&>(entity));
    }
}
