#include <abyss/modules/Adv/base/Engine.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Adv
{
    Engine::Engine(AdvObj* pObj):
        m_pObj(pObj)
    {
        this->setColor(s3d::Palette::White);
    }
    void Engine::onStart()
    {
        m_skip = m_pObj->find<SkipCtrl>();

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
        m_time += m_pObj->getModule<GlobalTime>()->deltaTime();
        return m_stream.resume();
    }
    void Engine::addCommand(std::function<void(AdvObj*)> callback)
    {
        class Callback : public ICommand
        {
        public:
            Callback(AdvObj* pObj, std::function<void(AdvObj*)>&& callback):
                m_pObj(pObj),
                m_callback(std::move(callback))
            {}
            void onStart() override
            {
                if (m_callback) {
                    m_callback(m_pObj);
                }
            }
            Coro::Fiber<> onCommand()override
            {
                co_return;
            }
        private:
            AdvObj* m_pObj;
            std::function<void(AdvObj*)> m_callback;
        };
        m_commands.push(std::make_shared<Callback>(m_pObj, std::move(callback)));
    }
    void Engine::addCommand(std::shared_ptr<ICommand> command)
    {
        m_commands.push(command);
    }
    void Engine::setCharaKind(const CharaKind& kind)
    {
        m_sentence.setKind(kind);
    }
    void Engine::setLook(const LookType & look)
    {
        m_sentence.setLook(look);
    }
    void Engine::setEmote(const Emote& emote)
    {
        m_sentence.setEmote(emote);
    }
    void Engine::setName(const Name& name)
    {
        m_sentence.setName(name);
    }
    void Engine::append(const char32_t ch)
    {
        m_sentence.getMessage().append(ch, m_time);
    }
    Engine& Engine::setColor(const s3d::Optional<s3d::ColorF>& color)
    {
        if (color) {
            m_color.push(*color);
        } else if (!m_color.empty()) {
            m_color.pop();
        }
        m_sentence.getMessage().append(
            Tag::Color{ m_color.top()}
        );
        return *this;
    }
    Engine& Engine::setIsShake(bool isShake)
    {
        m_isShake = isShake;
        m_sentence.getMessage().append(
            Tag::Shake{ isShake }
        );
        return *this;
    }
    void Engine::clearMessage()
    {
        auto& message = m_sentence.getMessage();
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
        if (m_sentence.getMessage().length() > 0) {
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
