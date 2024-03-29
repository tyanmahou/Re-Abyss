#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>

#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>

#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Main.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Behavior.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/RetireCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/ParentObserver.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/TentacleUtil.hpp>

#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Tentacle/TentacleVM.hpp>
#include <Siv3D.hpp>

namespace
{
	class Presenter;
}

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void Builder::Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc)
	{
		// Main
		{
			pActor->attach<Main>(pActor, desc);
		}
		// Body
		{
			const Vec2 offset = desc.offset + s3d::Circular9(desc.distOffset, desc.rotate);
			pActor->attach<Body>(pActor)
				->initPos(parent->find<Body>()->getPos() + offset)
				.noneResistanced();

			pActor->attach<BodyUpdater>(pActor);
		}

		// 回転
		{
			pActor->attach<RotateCtrl>()
				->setRotate(desc.rotate);
		}
		// 状態
		{
			pActor->attach<StateCtrl>(pActor)
				->changeState<WaitState>()
				;
		}

		// 衝突
		{
			auto colFunc = [
				body = pActor->find<Body>(),
				rotate = pActor->find<RotateCtrl>()
			]()->CShape {
				return TentacleUtil::Shape(body->getPos(), rotate->getRotate());
			};
			auto collider = pActor->attach<Collider>();
			collider->add(colFunc);

			pActor->attach<ColCtrl>(pActor)
				->addBranch()
				->addNode<Col::Node>(collider->main())
				.setLayer(ColSys::LayerGroup::Enemy)
				.attach<Col::Mover>(pActor)
				.attach<Col::Attacker>(pActor, 1)
				.attach<Col::Receiver>(pActor)
				;
		}
		{
			pActor->attach<RetireCtrl>(pActor);
		}
		// Shake
		{
			pActor->attach<ShakeCtrl>(pActor);
		}
		// Behavior
		{
			auto behavior = pActor->attach<BehaviorCtrl>(pActor);
			switch (desc.kind)
			{
			case Kind::Stab:
				behavior->setBehavior(Behavior::Stab);
				break;
			case Kind::PursuitStab:
				behavior->setBehavior(Behavior::PursuitStab);
				break;
			default:
				break;
			}
		}
		// 親監視
		{
			pActor->attach<ParentObserver>(pActor, parent);
		}
		// 描画制御
		{
			pActor->attach<VModel>()
				->setPresenter<Presenter>(pActor, parent);
		}
	}
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Enemy::KingDux;
	using namespace abyss::Actor::Enemy::KingDux::Tentacle;

	class Presenter : public IVModelPresenter<TentacleVM>
	{
	public:
		Presenter(ActorObj* pActor, ActorObj* parent) :
			m_pActor(pActor),
			m_parentColor(parent->find<ColorCtrl>()),
			m_view(std::make_unique<TentacleVM>())
		{}
	private:
		TentacleVM* bind() const final
		{
			s3d::ColorF colorMul(1, 1);
			s3d::ColorF colorAdd(0, 0);
			if (m_parentColor) {
				colorMul = m_parentColor->colorMul();
				colorAdd = m_parentColor->colorAdd();
			}
			return &m_view->setTime(m_pActor->getTimeSec())
				.setPos(m_body->getPos() + m_shake->getShakeOffset())
				.setRotate(m_rotate->getRotate())
				.setColorMul(colorMul)
				.setColorAdd(colorAdd)
				;
		}
		void onStart() final
		{
			m_body = m_pActor->find<Body>();
			m_shake = m_pActor->find<ShakeCtrl>();
			m_rotate = m_pActor->find<RotateCtrl>();
		}
	private:
		ActorObj* m_pActor = nullptr;
		Ref<ColorCtrl> m_parentColor;

		Ref<Body> m_body;
		Ref<ShakeCtrl> m_shake;
		Ref<RotateCtrl> m_rotate;

		std::unique_ptr<TentacleVM> m_view;
	};
}
