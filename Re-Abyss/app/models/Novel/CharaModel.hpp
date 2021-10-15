#pragma once
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Name.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <Siv3D/Texture.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Novel
{
    class CharaModel
    {
    public:
        CharaModel& setKind(CharaKind kind)
        {
            m_kind = kind;
            return *this;
        }
        [[nodiscard]] CharaKind getKind() const
        {
            return m_kind;
        }
        CharaModel& setName(const Name& name)
        {
            m_name = name;
            return *this;
        }
        [[nodiscard]] const Name& getName()const
        {
            return m_name;
        }
        CharaModel& setFacePath(const s3d::FilePath& facePath)
        {
            m_facePath = facePath;
            return *this;
        }
        [[nodiscard]] const s3d::FilePath& getFacePath()const
        {
            return m_facePath;
        }

        [[nodiscard]] bool isFindFace(const Face& face) const;

        [[nodiscard]] s3d::Texture getFace(const Face& face) const;
    private:
        CharaKind m_kind{};
        Name m_name;
        s3d::FilePath m_facePath;
    };
}