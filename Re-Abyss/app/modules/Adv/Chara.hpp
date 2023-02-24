#pragma once
#include <abyss/modules/Adv/CharaKind.hpp>
#include <abyss/modules/Adv/Name.hpp>
#include <abyss/modules/Adv/Face.hpp>
#include <Siv3D/Texture.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Adv
{
    class Chara
    {
    public:
        Chara& setKind(CharaKind kind)
        {
            m_kind = kind;
            return *this;
        }
        [[nodiscard]] CharaKind getKind() const
        {
            return m_kind;
        }
        Chara& setName(const Name& name)
        {
            m_name = name;
            return *this;
        }
        [[nodiscard]] const Name& getName()const
        {
            return m_name;
        }
        Chara& setFacePath(const s3d::FilePath& facePath)
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
