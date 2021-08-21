#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

#include <abyss/components/Actor/Commons/Locator.hpp>
#include <abyss/components/UI/Common/CustomDraw.hpp>

#include <abyss/views/UI/SpeechBalloon/SpeechBalloonVM.hpp>

namespace
{
    class Drawer;
}
namespace abyss::UI::SpeechBalloon
{
    void Builder::Build(UIObj* pUi, Actor::ActorObj* actor)
    {
        // 描画制御
        {
			pUi->attach<CustomDraw>()
				->setDrawer<Drawer>(pUi, actor);
        }
    }
}

namespace
{
	using namespace abyss;
	using namespace abyss::UI;
	using namespace abyss::UI::SpeechBalloon;

	using namespace abyss::Actor;

	class Drawer : public CustomDraw::IImpl
	{
	public:
		Drawer(UIObj* pUi, ActorObj* pActor) :
			m_pUi(pUi),
			m_pActor(pActor),
			m_view(std::make_unique<SpeechBalloonVM>())
		{}

		void onStart() override
		{
			m_locator = m_pActor->find<ILocator>();
		}
		void onDraw() const override
		{
			m_view
				->setPos(m_locator->getCenterPos())
				.setTime(m_pActor->getDrawTimeSec())
				.draw();
		}
	private:
		UIObj* m_pUi;
		ActorObj* m_pActor;

		Ref<ILocator> m_locator;
		std::unique_ptr<SpeechBalloonVM> m_view;
	};
}