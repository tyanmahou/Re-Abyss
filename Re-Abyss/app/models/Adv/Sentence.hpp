#pragma once
#include <abyss/values/Adv/CharaKind.hpp>
#include <abyss/values/Adv/LookType.hpp>
#include <abyss/values/Adv/Name.hpp>
#include <abyss/values/Adv/Emote.hpp>
#include <abyss/modules/Adv/TagString.hpp>

namespace abyss::Adv
{
    /// <summary>
    /// セリフ1つの情報
    /// </summary>
    class Sentence
    {
    public:
        Sentence& setKind(CharaKind kind)
        {
            m_kind = kind;
            return *this;
        }
        CharaKind getKind() const
        {
            return m_kind;
        }

        Sentence& setLook(LookType look)
        {
            m_look = look;
            return *this;
        }

        LookType getLook() const
        {
            return m_look;
        }

        bool isLookLeft() const
        {
            return m_look == LookType::Left;
        }
        bool isLookRight() const
        {
            return m_look == LookType::Right;
        }
        Sentence& setEmote(const Emote& emote)
        {
            m_emote = emote;
            return *this;
        }
        const Emote& getEmote() const
        {
            return m_emote;
        }

        Sentence& setName(const Name& name)
        {
            m_name = name;
            return *this;
        }
        const Name& getName()const
        {
            return m_name;
        }
        
        Sentence& setMessage(const TagString& message)
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
        LookType m_look{};
        Emote m_emote;
        Name m_name;
        TagString m_message;
    };
}
