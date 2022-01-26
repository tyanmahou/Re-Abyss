#include <abyss/modules/Decor/DecorGraphics.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/services/Decor/DecorService.hpp>
#include <abyss/entities/Decor/AnimationEntity.hpp>
#include <abyss/entities/Decor/GraphicsEntity.hpp>

namespace abyss::Decor
{
    void DecorGraphics::Anime::add(s3d::uint32 gId, double duration)
    {
        m_frames.push_back(Frame{
            .gId = gId,
            .duration = duration
            });
        m_maxDuration += duration;
    }
    s3d::uint32 DecorGraphics::Anime::getGId(double time) const
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
    bool DecorGraphics::Anime::isEmpty() const
    {
        return m_frames.isEmpty();
    }
    DecorGraphics::DecorGraphics(IDecorService* service)
    {
        for (const auto& [gId, graphics] : service->getGraphics()) {
            Info info{
                .filePath = graphics.filePath,
                .offset = graphics.offset,
                .size = graphics.size
            };
            this->addInfo(gId, std::move(info));
        }
        for (const auto& [gId, animes] : service->getAnimations()) {
            Anime anime;
            for (const auto& elm : animes) {
                anime.add(elm.toGId, elm.timeMilliSec);
            }
           this->addAnime(gId, std::move(anime));
        }
    }
    void DecorGraphics::addInfo(s3d::uint32 gId, const Info& info)
    {
        m_infos[gId] = info;
    }
    void DecorGraphics::addInfo(s3d::uint32 gId, Info&& info)
    {
        m_infos[gId] = std::move(info);
    }
    void DecorGraphics::addAnime(s3d::uint32 gId, const Anime& anime)
    {
        m_animes[gId] = anime;
    }
    void DecorGraphics::addAnime(s3d::uint32 gId, Anime&& anime)
    {
        m_animes[gId] = std::move(anime);
    }
    s3d::uint32 DecorGraphics::getAnimGId(s3d::uint32 gId, double time)
    {
        if (!m_animes[gId].isEmpty()) {
            gId = m_animes.at(gId).getGId(time);
        }
        return gId;
    }
    s3d::TextureRegion DecorGraphics::getTexture(s3d::uint32 gId, double time)
    {
        auto rawInfo = m_infos[gId];
        auto size = rawInfo.size;
        gId = this->getAnimGId(gId, time);
        if (m_textures.find(gId) != m_textures.end()) {
            return m_textures.at(gId).resized(size);
        }
        auto info = m_infos[gId];
        s3d::Texture tex(Resource::Assets::Main()->load(info.filePath, Path::Root));
        return m_textures[gId] = tex(info.offset, info.size);
    }
}