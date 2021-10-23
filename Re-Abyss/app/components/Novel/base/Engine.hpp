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
    public:
        void append(const char32_t ch);

        Engine& setColor(const s3d::Optional<s3d::ColorF>& color);

        const TagString& getMessage() const
        {
            return m_serif.getMessage();
        }
        bool isInputWait() const
        {
            return m_isInputWait;
        }
        void setIsInputWait(bool isInputWait)
        {
            m_isInputWait = isInputWait;
        }
    private:
        TalkObj* m_pTalk;

        SerifModel m_serif;

        std::stack<s3d::ColorF> m_color;

        bool m_isInputWait = false;

        // コマンド
        Coro::TaskHolder<> m_stream;
        std::queue<std::shared_ptr<ICommand>> m_commands;
        bool m_doneCurrentInit = false;

        double m_time = 0;
    };
}