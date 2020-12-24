#include "FaceTableModel.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Event::Talk
{
    void FaceTableModel::add(const s3d::String& actor, const s3d::FilePath& jsonPath)
    {
        m_actors[actor] = Resource::Assets::Main()->loadTexturePacker(jsonPath);
    }
    bool FaceTableModel::isContain(const s3d::String& actor, const s3d::String& kind) const
    {
        if (m_actors.find(actor) == m_actors.end()) {
            return false;
        }
        const auto& texture = m_actors.at(actor);
        return texture.isContain(kind);
    }
    s3d::Texture FaceTableModel::getFace(const s3d::String& actor, const s3d::String& kind) const
    {
        return m_actors.at(actor)(kind);
    }
}
