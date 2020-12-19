#include "Builder.hpp"

#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actors/Enemy/Schield/State/WaitState.hpp>
#include <abyss/components/Actors/Enemy/Schield/FaceCtrl.hpp>

namespace
{
    class Collider;
	class ViewBinder;
}
namespace abyss::Actor::Enemy::Schield
{
	void Builder::Build(IActor* pActor, const SchieldEntity& entity)
	{
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setColliderImpl<Collider>(pActor)
            .setAudioSettingGroupPath(U"Enemy/Schield/schield.aase")
            .setInitState<WaitState>()
        );

        // 顔制御
        {
            pActor->attach<FaceCtrl>(pActor);
        }
        // 描画制御
        {
            pActor->attach<ViewCtrl<SchieldVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
	}
}


namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::Schield;

    /// <summary>
    /// コライダー
    /// </summary>
    class Collider final : public CustomCollider::IImpl
    {
    public:
        Collider(IActor* pActor):
            m_pActor(pActor)
        {}
        void onStart() override
        {
            m_face = m_pActor->find<FaceCtrl>();
        }
        CShape getCollider() const override
        {
            if (m_face->isOnFace()) {
                return m_face->getCollider();
            }
            return s3d::none;
        }
    private:
        IActor* m_pActor;
        Ref<FaceCtrl> m_face;
    };

    /// <summary>
    /// 描画
    /// </summary>
    class ViewBinder : public ViewCtrl<SchieldVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;

        std::unique_ptr<SchieldVM> m_view;
    private:
        SchieldVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<SchieldVM>())
        {}
    };
}
