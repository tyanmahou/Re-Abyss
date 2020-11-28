#include "Task.hpp"

namespace abyss::Coro
{
    bool Task::moveNext() const
    {
        if (!m_coro) {
            return false;
        }
        if (m_coro.done()) {
            return false;
        }
        // 他のコルーチンが割り込み中はそちらを実行
        auto& next = m_coro.promise().next;
        if (next) {
            if (!next->moveNext()) {
                next = std::nullopt;
            } else {
                return true;
            }
        }
        m_coro.resume();
        return !m_coro.done();
    }
}