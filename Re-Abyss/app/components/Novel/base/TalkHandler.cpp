#include "TalkHandler.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Novel
{
    TalkHandler::TalkHandler(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}
    void TalkHandler::setup(Executer executer)
    {}
    void TalkHandler::onStart()
    {
        auto task = [this]()->Coro::Task<> {
            while (!m_commands.empty()) {
                auto& front = m_commands.front();
                front->onStart();
                m_doneCurrentInit = true;

                co_await front->onCommand();

                front->onEnd();
                m_commands.pop();
                m_doneCurrentInit = false;
            }
            co_return;
        };
        m_stream.reset(task);
    }
    void TalkHandler::onEnd()
    {
        // 残りのコマンドを処理する
        while (!m_commands.empty()) {
            auto& front = m_commands.front();
            if (!m_doneCurrentInit) {
                front->onStart();
                m_doneCurrentInit = true;
            }
            front->onEnd();
            m_commands.pop();
            m_doneCurrentInit = false;
        }
    }
    bool TalkHandler::update()
    {
        if (InputManager::Start.down()) {
            // skip
            return false;
        }
        return m_stream.moveNext();
    }
}
