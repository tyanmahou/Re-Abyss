#include <abyss/components/Novel/base/Engine.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
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

        this->resetStream();
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
        return m_stream.resume();
    }
    void Engine::addCommand(std::function<void(TalkObj*)> callback)
    {
        class Callback : public ICommand
        {
        public:
            Callback(TalkObj* pTalk, std::function<void(TalkObj*)>&& callback):
                m_pTalk(pTalk),
                m_callback(std::move(callback))
            {}
            void onStart() override
            {
                if (m_callback) {
                    m_callback(m_pTalk);
                }
            }
            Coro::Fiber<> onCommand()override
            {
                co_return;
            }
        private:
            TalkObj* m_pTalk;
            std::function<void(TalkObj*)> m_callback;
        };
        m_commands.push(std::make_shared<Callback>(m_pTalk, std::move(callback)));
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
    void Engine::resetStream()
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
                    co_yield {};
                }
            };
            while (!m_commands.empty()) {
                auto& front = m_commands.front();
                front->onStart();
                m_doneCurrentInit = true;

                co_await (
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
