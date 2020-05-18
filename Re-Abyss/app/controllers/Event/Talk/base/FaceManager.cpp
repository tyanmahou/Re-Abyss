#include "FaceManager.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::Event::Talk
{
    void FaceManager::add(const s3d::String& actor, const s3d::FilePath& jsonPath)
    {
        m_actors[actor] = ResourceManager::Main()->loadTexturePacker(jsonPath);
    }
    bool FaceManager::isContain(const s3d::String& actor, const s3d::String& kind) const
    {
        if (m_actors.find(actor) == m_actors.end()) {
            return false;
        }
        const auto& texture = m_actors.at(actor);
        return texture.isContain(kind);
    }
    s3d::Texture FaceManager::getFace(const s3d::String& actor, const s3d::String& kind) const
    {
        return m_actors.at(actor)(kind);
    }
}
