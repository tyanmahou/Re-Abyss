#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Novel
{
    class Face
    {
    public:
        Face():
            Face(U"default")
        {}
        Face(const s3d::String& str) :
            m_face(str)
        {}

        operator const s3d::String&() const
        {
            return m_face;
        }
    private:
        s3d::String m_face;
    };
}