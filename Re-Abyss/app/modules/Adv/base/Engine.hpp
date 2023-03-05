#pragma once
#include <memory>
#include <stack>
#include <queue>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/modules/Adv/base/SkipCtrl.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/models/Adv/Sentence.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Adv
{
    class Engine : public IComponent
    {
    public:
        Engine(AdvObj* pObj);

        void onStart() override;
        void onEnd() override;

        bool update();

        template<class T, class ... Args>
        void addCommand(Args&&... args)
        {
            addCommand(std::make_shared<T>(m_pObj, std::forward<Args>(args)...));
        }

        void addCommand(std::function<void(AdvObj*)> callback);

        void addCommand(std::shared_ptr<ICommand> command);

        const Sentence& getSentence() const
        {
            return m_sentence;
        }
        const TagString& getPrevMessage() const
        {
            return m_prevMessage;
        }
        double getTime() const
        {
            return m_time;
        }
    public:
        void setCharaKind(const CharaKind& kind);
        void setLook(const LookType& look);
        void setEmote(const Emote& emote);

        void setName(const Name& name);
        void append(const char32_t ch);

        Engine& setColor(const s3d::Optional<s3d::ColorF>& color);
        Engine& setIsShake(bool isShake);
        bool isInputWait() const
        {
            return m_isInputWait;
        }
        void setIsInputWait(bool isInputWait)
        {
            m_isInputWait = isInputWait;
        }

        /// <summary>
        /// メッセージをクリア
        /// </summary>
        void clearMessage();

        /// <summary>
        /// メッセージを完全にクリア
        /// </summary>
        void clearBuffer();
    private:
        void resetStream();
    private:
        AdvObj* m_pObj;

        Sentence m_sentence;
        TagString m_prevMessage;
        std::stack<s3d::ColorF> m_color;
        bool m_isShake = false;
        bool m_isInputWait = false;

        // コマンド
        Coro::FiberHolder<> m_stream;
        std::queue<std::shared_ptr<ICommand>> m_commands;
        bool m_doneCurrentInit = false;

        double m_time = 0;

        Ref<SkipCtrl> m_skip;
    };
}
