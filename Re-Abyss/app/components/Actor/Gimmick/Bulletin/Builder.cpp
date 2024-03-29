#include <abyss/components/Actor/Gimmick/Bulletin/Builder.hpp>

#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Gimmick/Bulletin/Talkable.hpp>
#include <abyss/views/Actor/Gimmick/Bulletin/BulletinVM.hpp>

namespace
{
	class Presenter;
}

namespace abyss::Actor::Gimmick::Bulletin
{
    void Builder::Build(ActorObj* pActor, const BulletinEntity& entity)
    {
		pActor->setDestoryTiming(DestoryTiming::CheckIn);

		// 座標
		{
			pActor->attach<Locator>()
				->setPos(entity.pos);
		}

		// コライダー
		{
			pActor->attach<Collider>()
				->add<Col::CircleCollider>(pActor)
				->setRadius(30.0);
		}

		// 会話制御
		{
			pActor->attach<Talkable>(pActor, entity.event);
		}

		// 描画
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
	using namespace abyss::Actor::Gimmick::Bulletin;

	class Presenter : public IVModelPresenter<BulletinVM>
	{
	public:
		Presenter(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<BulletinVM>())
		{}

		void onStart() override
		{
			m_locator = m_pActor->find<ILocator>();
		}
		BulletinVM* bind() const override
		{
			return &m_view
				->setPos(m_locator->getCenterPos());
		}
	private:
		ActorObj* m_pActor;

		Ref<ILocator> m_locator;
		std::unique_ptr<BulletinVM> m_view;
	};
}
namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::Bulletin>;
    template<>
    void BuilderFromEntity<GimmickType::Bulletin>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        Bulletin::Builder::Build(pActor, static_cast<const BulletinEntity&>(entity));
    }
}
