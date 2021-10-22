#pragma once
#include <memory>
#include <stack>
#include <queue>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/utils/Coro/TaskHolder/TaskHolder.hpp>
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/types/Novel/Side.hpp>
#include <abyss/types/Novel/Name.hpp>
#include <abyss/types/Novel/TagString.hpp>
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
    public:
        void append(const char32_t ch);

        Engine& setColor(const s3d::Optional<s3d::ColorF>& color);

        const TagString& getMessage() const
        {
            return m_message;
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

        CharaKind m_charaKind;
        Side m_side;
        Face m_face;
        Name m_name;

        TagString m_message;

        std::stack<s3d::ColorF> m_color;

        bool m_isInputWait = false;

        // コマンド
        Coro::TaskHolder<> m_stream;
        std::queue<std::shared_ptr<ICommand>> m_commands;
        bool m_doneCurrentInit = false;
    };
}