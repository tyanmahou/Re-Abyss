#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Adv
{
    class Emote
    {
    public:
        Emote():
            Emote(U"default")
        {}
        Emote(const s3d::String& str) :
            m_emote(str)
        {}

        operator const s3d::String&() const
        {
            return m_emote;
        }
    private:
        s3d::String m_emote;
    };
}
