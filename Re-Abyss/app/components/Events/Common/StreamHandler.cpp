#include "StreamHandler.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Event;

    Coro::Task<> ExecuteStrems(IEvent* pEvent)
    {
        s3d::Array<Coro::Task<>> tasks;
        for (auto&& stream : pEvent->finds<IStream>()) {
            tasks.push_back(stream->onExecute());
        }
        while (true) {
            for (auto& task : tasks) {
                task.moveNext();
            }

            if (tasks.all([](const Coro::Task<>& t) {return t.isDone(); })) {
                co_return;
            }

            co_yield{};
        }
    }
}
namespace abyss::Event
{
    StreamHandler::StreamHandler(IEvent* pEvent):
        m_pEvent(pEvent)
    {}
    void StreamHandler::setup(Depends depends)
    {
        depends.on<IComponent>().addAfter<IStream>();
    }
    void StreamHandler::onStart()
    {
        m_stream = std::make_unique<Coro::Task<>>(ExecuteStrems(m_pEvent));
    }
    bool StreamHandler::update()
    {
        if (!m_stream) {
            return false;
        }
        return m_stream->moveNext();
    }
}
