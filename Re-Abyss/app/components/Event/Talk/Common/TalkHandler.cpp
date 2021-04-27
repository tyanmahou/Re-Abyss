#include "TalkHandler.hpp"
#include <abyss/modules/Event/Talk/TalkObj.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Event::Talk;

    Coro::Task<> ExecuteStrems(TalkObj* pTalk)
    {
        s3d::Array<Coro::Task<>> tasks;
        for (auto&& talker : pTalk->finds<ITalker>()) {
            tasks.push_back(talker->onTalk());
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
namespace abyss::Event::Talk
{
    TalkHandler::TalkHandler(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void TalkHandler::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<ITalker>();
    }
    void TalkHandler::onStart()
    {
        m_stream = std::make_unique<Coro::Task<>>(ExecuteStrems(m_pTalk));
    }
    bool TalkHandler::update()
    {
        if (!m_stream) {
            return false;
        }
        return m_stream->moveNext();
    }
}
