#pragma once
#include <Siv3D/Optional.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/StringView.hpp>
#include <Siv3D/Stopwatch.hpp>
namespace abyss::Novel
{
    class OldSerifModel
    {
    public:
        enum class Side : bool
        {
            Left,
            Right,
        };
        using Message = std::pair<s3d::String, s3d::String>;
    private:
        s3d::Optional<s3d::String> m_actorName;
        Side m_side = Side::Left;
        s3d::Array<Message> m_messages;

        s3d::Stopwatch m_stopwatch;
        size_t m_messageIndex = 0;
        std::function<bool()> m_onInput;
        s3d::int32 m_strIndex = 0;
        bool m_isAll = false;
    public:

        OldSerifModel();

        bool update();

        OldSerifModel& setActorName(const s3d::String& actorName)
        {
            m_actorName = actorName;
            return *this;
        }
        const s3d::Optional<s3d::String>& getActorName()const
        {
            return m_actorName;
        }

        OldSerifModel& setSide(Side side)
        {
            m_side = side;
            return *this;
        }
        Side getSide() const
        {
            return m_side;
        }
        OldSerifModel& addMessage(const Message& message)
        {
            m_messages.push_back(message);
            return *this;
        }
        const s3d::Array<Message>& getMessages()const
        {
            return m_messages;
        }
        const s3d::String& getMessage(size_t index)const
        {
            return m_messages[index].second;
        }
        s3d::int32 getStrIndex()const
        {
            return m_strIndex;
        }
        bool isAll()const
        {
            return m_isAll;
        }
        size_t size() const
        {
            return m_messages.size();
        }
        bool isLeft()const
        {
            return m_side == Side::Left;
        }
        bool isRight()const
        {
            return m_side == Side::Right;
        }
        s3d::String getPrev() const;
        const s3d::String& getCurrent() const;
        const s3d::String& getCurrentKind()const;

        bool isEnd()const;
    };
}