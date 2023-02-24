#pragma once
#include <abyss/modules/Adv/CharaKind.hpp>
#include <abyss/modules/Adv/Side.hpp>
#include <abyss/modules/Adv/Name.hpp>
#include <abyss/modules/Adv/Face.hpp>
#include <abyss/modules/Adv/TagString.hpp>

namespace abyss::Adv
{
    /// <summary>
    /// セリフ1つの情報
    /// </summary>
    class Serif
    {
    public:
        Serif& setKind(CharaKind kind)
        {
            m_kind = kind;
            return *this;
        }
        CharaKind getKind() const
        {
            return m_kind;
        }

        Serif& setSide(Side side)
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
        Serif& setFace(const Face& face)
        {
            m_face = face;
            return *this;
        }
        const Face& getFace() const
        {
            return m_face;
        }

        Serif& setName(const Name& name)
        {
            m_name = name;
            return *this;
        }
        const Name& getName()const
        {
            return m_name;
        }
        
        Serif& setMessage(const TagString& message)
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
