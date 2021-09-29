#include "Builder.hpp"

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Ooparts/CommonBuilder.hpp>

#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>
#include <abyss/views/Actor/Ooparts/Nyan/NyanVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Ooparts::Nyan
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
    {
        CommonBuilder::Build(pActor, parent);

        // 描画制御
        {
            pActor
                ->find<VModel>()
                ->setBinder<ViewBinder>(pActor);
        }
    };
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Ooparts;
    using namespace abyss::Actor::Ooparts::Nyan;

    class ViewBinder : public IVModelBinder<OopartsView>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<OopartsView> m_view;
    private:
        OopartsView* bind() const final
        {
            return  &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_view->setCharacter(std::make_shared<NyanVM>());
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<OopartsView>())
        {}
    };
}