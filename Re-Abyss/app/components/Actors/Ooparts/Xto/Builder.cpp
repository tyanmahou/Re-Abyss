#include "Builder.hpp"

#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Ooparts/CommonBuilder.hpp>


#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>
#include <abyss/views/Actors/Ooparts/Xto/XtoVM.hpp>
#include <abyss/views/Actors/Ooparts/base/ActDrawCallbackView.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Ooparts::Xto
{
    void Builder::Build(IActor* pActor, IActor* parent)
    {
        CommonBuilder::Build(pActor, parent);

        // 描画制御
        {
            pActor
                ->find<ViewCtrl<OopartsVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
    };
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Ooparts;
    using namespace abyss::Actor::Ooparts::Xto;

    class ViewBinder : public ViewCtrl<OopartsVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<OopartsVM> m_view;
    private:
        OopartsVM* bind() const final
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
            m_view->setCallback(std::make_unique<ActDrawCallbackView>(m_view.get(), m_pActor->getManager()));
            m_view->setCharacter(std::make_shared<XtoVM>());
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<OopartsVM>())
        {}
    };
}