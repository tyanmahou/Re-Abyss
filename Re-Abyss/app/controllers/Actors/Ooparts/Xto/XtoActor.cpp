#include "XtoActor.hpp"
#include <abyss/models/Actors/Commons/BodyModel.hpp>

#include <abyss/views/Actors/Ooparts/Xto/XtoVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Ooparts::Xto
{
    XtoActor::XtoActor(IActor* parent):
        OopartsActor(parent)
    {
        m_view->createBinder<ViewBinder>(this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Ooparts;
    using namespace abyss::Ooparts::Xto;

    class ViewBinder : public ViewModel<OopartsVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;

        std::unique_ptr<XtoVM> m_view;
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
            m_body = m_pActor->find<BodyModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<XtoVM>())
        {}
    };
}