#pragma once
#include <Siv3D/HashTable.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Event::Talk
{
    class FaceManager
    {
        s3d::HashTable<s3d::String, TexturePacker> m_actors;
    public:
        void add(const s3d::String& actor, const s3d::FilePath& jsonPath);

        [[nodiscard]] bool isContain(const s3d::String& actor, const s3d::String& kind) const;
        [[nodiscard]] s3d::Texture getFace(const s3d::String& actor, const s3d::String& kind) const;
    };
}