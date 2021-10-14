#include "TalkHandler.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Novel;

    Coro::Task<> ExecuteStreams(TalkObj* pTalk)
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
namespace abyss::Novel
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
        m_stream.reset(std::bind(::ExecuteStreams, m_pTalk));
    }
    bool TalkHandler::update()
    {
        return m_stream.moveNext();
    }
}
