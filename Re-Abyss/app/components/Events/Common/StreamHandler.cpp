#include "StreamHandler.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>

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
        auto streams = m_pEvent->finds<IStream>();
        if (streams.isEmpty()) {
            return;
        }

        auto task = [streams]()->Coro::Task<> {
            s3d::Array<Coro::Task<>> tasks;
            for (auto& stream : streams) {
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
        };
        m_stream = std::make_unique<Coro::Task<>>(task());
    }
    bool StreamHandler::update()
    {
        if (!m_stream) {
            return false;
        }
        return m_stream->moveNext();
    }
}
