#include <abyss/components/Actor/Enemy/Schield/Builder.hpp>

#include <abyss/entities/Actor/Enemy/SchieldEntity.hpp>
#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/utils/Collision/CShape.hpp>

#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/Schield/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/ShellCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCollider.hpp>

#include <abyss/views/Actor/Enemy/Schield/SchieldVM.hpp>

namespace
{
	class Presenter;
}
namespace abyss::Actor::Enemy::Schield
{
	void Builder::Build(ActorObj* pActor, const SchieldEntity& entity)
	{
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.footPos)
            .setBodyAnchor(BodyAnchor::BottomCenter)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setCollider<FaceCollider>(pActor)
            .setInitState<WaitState>()
            .setVModelPresenter<Presenter>(pActor)
        );

        // 顔制御
        {
            pActor->attach<FaceCtrl>(pActor);
        }
        // 甲羅
        {
            pActor->attach<ShellCtrl>(pActor);
        }
	}
}


namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::Schield;

    /// <summary>
    /// 描画
    /// </summary>
    class Presenter : public IVModelPresenter<SchieldVM>
    {
    private:
        SchieldVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setMotion(m_motion->get<Motion>())
                .setAnimeTime(m_motion->animeTime())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<SchieldVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ColorCtrl> m_colorCtrl;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<SchieldVM> m_view;
    };
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::Schield>;
    template<>
    void BuilderFromEntity<EnemyType::Schield>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        Schield::Builder::Build(pActor, static_cast<const SchieldEntity&>(entity));
    }
}

