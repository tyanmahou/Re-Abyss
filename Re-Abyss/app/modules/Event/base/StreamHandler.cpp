#include <abyss/modules/Event/base/StreamHandler.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Event;

    Coro::Fiber<> ExecuteStrems(EventObj* pEvent)
    {
        s3d::Array<Coro::Fiber<>> tasks;
        for (auto&& stream : pEvent->finds<IStream>()) {
            tasks.push_back(stream->onExecute());
        }
        while (true) {
            for (auto& task : tasks) {
                task.resume();
            }

            if (tasks.all([](const Coro::Fiber<>& t) {return t.isDone(); })) {
                co_return;
            }

            co_yield{};
        }
    }
}
namespace abyss::Event
{
    StreamHandler::StreamHandler(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void StreamHandler::setup(Executer executer)
    {
        executer.onStart().addAfter<IStream>();
    }
    void StreamHandler::onStart()
    {
        m_stream = std::make_unique<Coro::Fiber<>>(ExecuteStrems(m_pEvent));
    }
    bool StreamHandler::update()
    {
        if (!m_stream) {
            return false;
        }
        return m_stream->resume();
    }
}
