#pragma once
#include <memory>
#include <stack>
#include <queue>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/utils/Coro/TaskHolder/TaskHolder.hpp>
#include <abyss/models/Novel/SerifModel.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Novel
{
    class Engine : public IComponent
    {
    public:
        Engine(TalkObj* pTalk);

        void onStart() override;
        void onEnd() override;

        bool update();

        template<class T, class ... Args>
        void addCommand(Args&&... args)
        {
            addCommand(std::make_shared<T>(m_pTalk, std::forward<Args>(args)...));
        }
        void addCommand(std::shared_ptr<ICommand> command);

        const SerifModel& getSerif() const
        {
            return m_serif;
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
        void setSide(const Side& side);
        void setFace(const Face& face);

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

        void clearMessage();
    private:
        TalkObj* m_pTalk;

        SerifModel m_serif;
        TagString m_prevMessage;
        std::stack<s3d::ColorF> m_color;
        bool m_isShake = false;
        bool m_isInputWait = false;

        // コマンド
        Coro::TaskHolder<> m_stream;
        std::queue<std::shared_ptr<ICommand>> m_commands;
        bool m_doneCurrentInit = false;

        double m_time = 0;
    };
}