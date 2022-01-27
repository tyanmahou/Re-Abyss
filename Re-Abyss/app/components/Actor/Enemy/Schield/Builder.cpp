#include <abyss/components/Actor/Enemy/Schield/Builder.hpp>

#include <abyss/entities/Actor/Enemy/SchieldEntity.hpp>
#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/Schield/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/ShellCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCollider.hpp>

#include <abyss/views/Actor/Enemy/Schield/SchieldVM.hpp>

namespace
{
	class ViewBinder;
}
namespace abyss::Actor::Enemy::Schield
{
	void Builder::Build(ActorObj* pActor, const SchieldEntity& entity)
	{
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setCollider<FaceCollider>(pActor)
            .setAudioSettingGroupPath(U"Enemy/Schield/Schield.aase")
            .setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
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
    class ViewBinder : public IVModelBinder<SchieldVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_damage;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<SchieldVM> m_view;
    private:
        SchieldVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_damage->isInInvincibleTime())
                .setMotion(m_motion->get<Motion>())
                .setAnimeTime(m_motion->animeTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_damage = m_pActor->find<DamageCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<SchieldVM>())
        {}
    };
}
