#include "IEvent.hpp"
#include <abyss/components/Events/Common/StreamHandler.hpp>
namespace abyss::Event
{
    IEvent::IEvent()
    {
        m_stream = this->attach<StreamHandler>(this);
    }

    bool IEvent::update()
    {
        return m_stream->update();
    }

}
