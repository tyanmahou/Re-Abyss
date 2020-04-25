#include "SerifModel.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Event::Talk
{
    SerifModel::SerifModel()
    {
        m_onInput = []() {
            return InputManager::A.down() || InputManager::B.down();
        };
    }
    bool SerifModel::update()
    {
        if (m_messageIndex >= m_messages.size()) {
            return false;
        }
        if (!m_stopwatch.isStarted()) {
            m_stopwatch.start();
        }
        const auto& message = m_messages[m_messageIndex];
        m_strIndex = m_stopwatch.ms() / 60;
        m_isAll = m_strIndex >= message.length();

        if (m_onInput()) {
            if (m_isAll) {
                ++m_messageIndex;
                if (m_messageIndex >= m_messages.size()) {
                    return false;
                }
                m_messageIndex %= m_messages.size();
                m_stopwatch.restart();
            } else {
                m_stopwatch.set(100000s);
            }
        }
        return true;
    }
    s3d::StringView SerifModel::getPrevView() const
    {
        return m_messageIndex > 0 ? m_messages[m_messageIndex -1] : U"";
    }
    s3d::StringView SerifModel::getCurrentView() const
    {
        return m_messages[m_messageIndex];
    }
    bool SerifModel::isEnd() const
    {
        return m_messageIndex >= m_messages.size();
    }
}
