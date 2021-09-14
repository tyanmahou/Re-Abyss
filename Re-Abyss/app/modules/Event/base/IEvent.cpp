#include "IEvent.hpp"
#include <abyss/components/Event/base/StreamHandler.hpp>
#include <abyss/components/Event/base/IUpdate.hpp>
#include <abyss/components/Event/base/ILastUpdate.hpp>

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
