#include <abyss/components/Novel/base/Engine.hpp>

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
        m_skip = m_pTalk->find<SkipCtrl>();

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
        if (m_skip && m_skip->isSkip()) {
            // skip
            m_skip->onSkip();
            return false;
        }
        return m_stream.moveNext();
    }
    void Engine::addCommand(std::shared_ptr<ICommand> command)
    {
        m_commands.push(command);
    }
    void Engine::setCharaKind(const CharaKind& kind)
    {
        m_serif.setKind(kind);
    }
    void Engine::setSide(const Side & side)
    {
        m_serif.setSide(side);
    }
    void Engine::setFace(const Face & face)
    {
        m_serif.setFace(face);
    }
    void Engine::setName(const Name& name)
    {
        m_serif.setName(name);
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
    Engine& Engine::setIsShake(bool isShake)
    {
        m_isShake = isShake;
        m_serif.getMessage().append(
            Tag::Shake{ isShake }
        );
        return *this;
    }
    void Engine::clearMessage()
    {
        auto& message = m_serif.getMessage();
        m_prevMessage = std::move(message);

        message.clear();
        m_time = 0;

        message.append(
            Tag::Color{ m_color.top() }
        );
        message.append(
            Tag::Shake{ m_isShake }
        );
    }
    void Engine::clearBuffer()
    {
        if (m_serif.getMessage().length() > 0) {
            this->clearMessage();
        }
        if (m_prevMessage.length() > 0) {
            m_prevMessage.clear();
        }
    }
}
