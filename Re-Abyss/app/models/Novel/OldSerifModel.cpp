#include "OldSerifModel.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Novel
{
    OldSerifModel::OldSerifModel()
    {
        m_onInput = []() {
            return InputManager::A.down() || InputManager::B.down();
        };
    }
    bool OldSerifModel::update()
    {
        if (m_messageIndex >= m_messages.size()) {
            return false;
        }
        if (!m_stopwatch.isStarted()) {
            m_stopwatch.start();
        }
        const auto& message = m_messages[m_messageIndex].second;
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
    s3d::String OldSerifModel::getPrev() const
    {
        return m_messageIndex > 0 ? m_messages[m_messageIndex -1].second : U"";
    }
    const s3d::String& OldSerifModel::getCurrent() const
    {
        return m_messages[m_messageIndex].second;
    }
    const s3d::String& OldSerifModel::getCurrentKind() const
    {
        return m_messages[m_messageIndex].first;
    }
    bool OldSerifModel::isEnd() const
    {
        return m_messageIndex >= m_messages.size();
    }
}
