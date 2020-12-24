#include "IEvent.hpp"
#include <abyss/components/Events/Common/StreamHandler.hpp>
#include <abyss/components/Events/base/IUpdate.hpp>
#include <abyss/components/Events/base/ILastUpdate.hpp>

namespace abyss::Event
{
    IEvent::IEvent()
    {
        m_stream = this->attach<StreamHandler>(this);
    }

    bool IEvent::update()
    {
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }

        const bool ret = m_stream->update();

        for (auto&& com : this->finds<ILastUpdate>()) {
            com->onLastUpdate();
        }
        return ret;
    }

}
