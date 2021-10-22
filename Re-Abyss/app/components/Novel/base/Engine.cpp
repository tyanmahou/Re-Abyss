#include "Engine.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <Siv3D.hpp>

namespace abyss::Novel
{
    Engine::Engine(TalkObj* pTalk):
        m_pTalk(pTalk)
    {
        this->setColor(s3d::Palette::White);
    }
    void Engine::onStart()
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
    void Engine::onEnd()
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
    bool Engine::update()
    {
        m_time += m_pTalk->getModule<GlobalTime>()->deltaTime();
        if (InputManager::Start.down()) {
            // skip
            return false;
        }
        return m_stream.moveNext();
    }
    void Engine::append(const char32_t ch)
    {
        m_serif.getMessage().append(ch, m_time);
    }
    Engine& Engine::setColor(const s3d::Optional<s3d::ColorF>& color)
    {
        if (color) {
            m_color.push(*color);
        } else if (!m_color.empty()) {
            m_color.pop();
        }
        m_serif.getMessage().append(
            Tag::Color{ m_color.top()}
        );
        return *this;
    }
}
