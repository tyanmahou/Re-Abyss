#include <abyss/modules/Adv/base/Process.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    Process::Process(AdvObj* pObj):
        m_pObj(pObj)
    {}

    bool Process::update()
    {
    }
    void Process::onStart()
    {
        m_skip = m_pObj->find<SkipCtrl>();

        this->resetStream();
    }
    void Process::onEnd()
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
    void Process::resetStream()
    {
        auto task = [this]()->Coro::Fiber<> {
            // スキップ制御
            bool isSkipped = false;
            auto skipCheck = [this, &isSkipped]()->Coro::Fiber<> {
                while (true) {
                    bool isSkipPrev = isSkipped;
                    if (isSkipped = (m_skip && m_skip->isSkip())) {
                        co_return;
                    }
                    if (isSkipPrev) {
                        m_skip->onSkip();
                    }
                    co_yield{};
                }
            };
            while (!m_commands.empty()) {
                auto& front = m_commands.front();
                front->onStart();
                m_doneCurrentInit = true;

                co_await(
                    skipCheck() | front->onCommand()
                );

                front->onEnd();
                m_commands.pop();
                m_doneCurrentInit = false;
            }
            if (isSkipped) {
                m_skip->onSkip();
            }
            co_return;
        };
        m_stream.reset(task);
    }
}
