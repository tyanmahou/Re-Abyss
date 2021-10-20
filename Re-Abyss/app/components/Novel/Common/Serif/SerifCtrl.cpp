#include "SerifCtrl.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/UI/Serif/Builder.hpp>

#include <Siv3D.hpp>
namespace abyss::Novel
{
    SerifCtrl::SerifCtrl(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void SerifCtrl::onStart()
    {
        m_pTalk->getModule<UIs>()
            ->create<UI::Serif::Builder>(m_pTalk->find<SerifCtrl>());
    }
    void SerifCtrl::onEnd()
    {}
    Coro::Task<> SerifCtrl::onCommand()
    {
        while (m_serifIndex < m_serifs.size()) {
            Stopwatch stopwatch(StartImmediately::Yes);

            while (true) {
                const auto& message = m_serifs[m_serifIndex].getMessage();
                m_strIndex = stopwatch.ms() / 60;
                bool isAll = m_strIndex >= message.length();

                if (InputManager::A.down() || InputManager::B.down()) {
                    if (isAll) {
                        // 次のメッセージ
                        ++m_serifIndex;
                        if (m_serifIndex >= m_serifs.size()) {
                            co_return;
                        }
                        break;
                    } else {
                        stopwatch.set(100000s);
                    }
                }
                co_yield{};
            }
            co_yield{};
        }
        co_return;
    }
    const SerifModel& SerifCtrl::getCurrent() const
    {
        return m_serifs[m_serifIndex];
    }
    const s3d::Optional<SerifModel>& SerifCtrl::getPrev() const
    {
        if (m_serifIndex == 0) {
            return s3d::none;
        }
        if (m_serifs[m_serifIndex].getKind() != m_serifs[m_serifIndex - 1].getKind()) {
            return s3d::none;
        }
        if (m_serifs[m_serifIndex].getSide() != m_serifs[m_serifIndex - 1].getSide()) {
            return s3d::none;
        }
        return m_serifs[m_serifIndex - 1];
    }
}
