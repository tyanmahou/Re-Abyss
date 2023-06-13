#include <abyss/components/Actor/Enemy/CaptainTako/Shot/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/ShotParam.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/DeadOnHItReceiver.hpp>
#include <abyss/components/Actor/Common/OutRoomChecker.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/Shot/State/BaseState.hpp>

#include <abyss/views/Actor/Enemy/CaptainTako/Shot/ShotVM.hpp>
namespace
{
    class Presenter;
}
namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, Forward forward)
    {
        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(pos)
                .setForward(forward)
                .noneResistanced()
                .setVelocityX(forward.signH() * ShotParam::Base::Speed);

            pActor->attach<BodyUpdater>(pActor);
        }

        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add<Col::CircleCollider>(pActor)
                ->setRadius(ShotParam::Base::ColRadius);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Mover>(pActor)
                .attach<Col::Attacker>(pActor, 1)
                ;

        }

        // 地形衝突
        {
            pActor->attach<MapCollider>(pActor, false);
        }
        // ヒット死亡
        {
            pActor->attach<DeadOnHItReceiver>(pActor);
        }
        // ルーム外死亡
        {
            pActor->attach<OutRoomChecker>(pActor);
        }
        // 死亡チェック
        {
            pActor->attach<DeadChecker>(pActor);
        }
        // サウンド
        {
            pActor->attach<AudioSource>(pActor);
        }
        // 描画制御
        {
            pActor->attach<VModel>()
                ->setPresenter<Presenter>(pActor);
        }
        // 状態
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<BaseState>()
                ;
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CaptainTako;
    using namespace abyss::Actor::Enemy::CaptainTako::Shot;

    class Presenter : public IVModelPresenter<ShotVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        std::unique_ptr<ShotVM> m_view;
    private:
        ShotVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
        }
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<ShotVM>())
        {}
    };
}
