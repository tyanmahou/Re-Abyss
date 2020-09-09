#include "NyanActor.hpp"
#include <abyss/components/Actors/Commons/Body.hpp>

#include <abyss/views/Actors/Ooparts/Nyan/NyanVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Ooparts::Nyan
{
    NyanActor::NyanActor(IActor* parent):
        OopartsActor(parent)
    {
        m_view->createBinder<ViewBinder>(this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Ooparts;
    using namespace abyss::Actor::Ooparts::Nyan;

    class ViewBinder : public ViewCtrl<OopartsVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;

        std::unique_ptr<NyanVM> m_view;
    private:
        OopartsVM* bind() const final
        {
            return  &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setManager(m_pActor->getManager())
                ;
        }
        void setup() final
        {
            m_body = m_pActor->find<Body>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<NyanVM>())
        {}
    };
}