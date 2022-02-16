#include <abyss/components/Actor/Common/BehaviorTest.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/debugs/Debug.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    BehaviorTest::BehaviorTest(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void BehaviorTest::onStart()
    {
        m_worldComment = m_pActor->getModule<WorldComment>()->getRequestor();
        m_body = m_pActor->find<Body>();
        if (Debug::Menu::IsDebug(Debug::DebugFlag::ActorTestBehavior)) {
            m_isActive = true;
            m_pActor->find<BehaviorCtrl>()->setSequence(std::bind_front(&BehaviorTest::doTest, this));
        }
    }
    void BehaviorTest::onPreDraw()
    {
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::ActorTestBehavior) && !m_isActive) {
            return;
        }
        if (m_actions.isEmpty()) {
            return;
        }
        String text = U"...";
        if (!m_isActive) {
            text = U"Inactive";
        } else if (m_worldComment->isSelected()) {
            if (m_isSelectable) {
                // 停止中でも動かせるようにここで選択可能
                if (KeyComma.down()) {
                    if (m_select == 0) {
                        m_select = m_actions.size() - 1;
                    } else {
                        --m_select;
                    }
                } else if (KeyPeriod.down()) {
                    if (m_select == m_actions.size() - 1) {
                        m_select = 0;
                    } else {
                        ++m_select;
                    }
                }
                text = U"◀ {} ▶"_fmt(m_actions[m_select].first);
            } else {
                text = U"  {}  "_fmt(m_actions[m_select].first);
            }
        }
        m_worldComment->comment(text, m_body->region().topCenter(), ColorF(0.8, 1.0, 1.0, 0.8));
    }
    BehaviorTest& BehaviorTest::setInitializer(const BehaviorFunc& initializer)
    {
        m_initializer = initializer;
        return *this;
    }
    BehaviorTest& BehaviorTest::setWaitAction(const BehaviorFunc& waitAction)
    {
        m_waitAction = waitAction;
        return *this;
    }
    BehaviorTest& BehaviorTest::registAction(const s3d::String& key, const BehaviorFunc& behavior)
    {
        m_actions.emplace_back(key, behavior);
        return *this;
    }
    Coro::Task<> BehaviorTest::doTest(BehaviorCtrl* behavior)
    {
        if (m_initializer) {
            behavior->setBehavior(m_initializer);
            co_await Coro::WaitUntil([behavior] {
                return behavior->isDoneBehavior();
            });
        }
        while (!m_actions.empty()) {
            if (m_waitAction) {
                behavior->setBehavior(m_waitAction);
                co_await Coro::WaitUntil([behavior] {
                    return behavior->isDoneBehavior();
                });
            }

            // 技選択
            while (true) {
                m_isSelectable = true;
                if (m_worldComment->isSelected()) {
                    if (KeySlash.down()) {
                        break;
                    }
                }
                co_yield{};
            }
            m_isSelectable = false;
            behavior->setBehavior(m_actions[m_select].second);
            co_await Coro::WaitUntil([behavior] {
                return behavior->isDoneBehavior();
            });
        }
        co_return;
    }
}
#endif
