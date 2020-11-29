#include "DecorGraphicsManager.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
namespace abyss
{
    void DecorGraphicsManager::Anime::add(s3d::uint32 gId, double duration)
    {
        m_frames.push_back(Frame{
            .gId = gId,
            .duration = duration
        });
        m_maxDuration += duration;
    }
    s3d::uint32 DecorGraphicsManager::Anime::getGId(double time) const
    {
        double modTime = std::fmod(time * 1000.0, m_maxDuration);
        double sum = 0;
        for (const auto& f : m_frames) {
            if (modTime < sum + f.duration) {
                return f.gId;
            }
            sum += f.duration;
        }
        return 0;
    }
    bool DecorGraphicsManager::Anime::isEmpty() const
    {
        return m_frames.isEmpty();
    }
    void DecorGraphicsManager::addInfo(s3d::uint32 gId, const Info& info)
    {
        m_infos[gId] = info;
    }
    void DecorGraphicsManager::addInfo(s3d::uint32 gId, Info&& info)
    {
        m_infos[gId] = std::move(info);
    }
    void DecorGraphicsManager::addAnime(s3d::uint32 gId, const Anime & anime)
    {
        m_animes[gId] = anime;
    }
    void DecorGraphicsManager::addAnime(s3d::uint32 gId, Anime&& anime)
    {
        m_animes[gId] = std::move(anime);
    }
    s3d::TextureRegion DecorGraphicsManager::getTexture(s3d::uint32 gId, double time)
    {
        auto rawInfo = m_infos[gId];
        auto size = rawInfo.size;
        if (!m_animes[gId].isEmpty()) {
            gId = m_animes.at(gId).getGId(time);
        }
        if (m_textures.find(gId) != m_textures.end()) {
            return m_textures.at(gId).resized(size);
        }
        auto info = m_infos[gId];
        s3d::Texture tex(Resource::Assets::Main()->loadTexture(info.filePath, Path::Root));
        return m_textures[gId] = tex(info.offset, info.size);
    }
}
