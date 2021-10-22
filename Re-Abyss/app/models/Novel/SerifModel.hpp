#pragma once
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Side.hpp>
#include <abyss/types/Novel/Name.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/types/Novel/TagString.hpp>

namespace abyss::Novel
{
    /// <summary>
    /// セリフ1つの情報
    /// </summary>
    class SerifModel
    {
    public:
        SerifModel& setKind(CharaKind kind)
        {
            m_kind = kind;
            return *this;
        }
        CharaKind getKind() const
        {
            return m_kind;
        }

        SerifModel& setSide(Side side)
        {
            m_side = side;
            return *this;
        }

        Side getSide() const
        {
            return m_side;
        }

        bool isLeft() const
        {
            return m_side == Side::Left;
        }
        bool isRight() const
        {
            return m_side == Side::Right;
        }
        SerifModel& setSide(const Face& face)
        {
            m_face = face;
            return *this;
        }
        const Face& getFace() const
        {
            return m_face;
        }

        SerifModel& setName(const Name& name)
        {
            m_name = name;
            return *this;
        }
        const Name& getName()const
        {
            return m_name;
        }
        
        SerifModel& setMessage(const TagString& message)
        {
            m_message = message;
            return *this;
        }
        TagString& getMessage()
        {
            return m_message;
        }
        const TagString& getMessage()const
        {
            return m_message;
        }
    private:
        CharaKind m_kind{};
        Side m_side{};
        Face m_face;
        Name m_name;
        TagString m_message;
    };
}