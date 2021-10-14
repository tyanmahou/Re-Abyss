#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Novel
{
    class FaceTableModel;

    class FaceTable : public IComponent
    {
    public:
        FaceTable(std::shared_ptr<FaceTableModel> faceTable);
        [[nodiscard]] bool isContain(const s3d::String& actor, const s3d::String& kind) const;
        [[nodiscard]] s3d::Texture getFace(const s3d::String& actor, const s3d::String& kind) const;
    private:
        std::shared_ptr<FaceTableModel> m_faceTable;
    };
}