#include <abyss/models/Adv/Chara.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    using namespace abyss::Resource;

    abyss::TexturePacker Load(const s3d::FilePath& path)
    {
        return Assets::Main()->loadTexturePacker(path);
    }
}

namespace abyss::Adv
{
    bool Chara::isFindFace(const Emote& emote) const
    {
        return ::Load(m_facePath).isContain(emote);
    }

    s3d::Texture Chara::getFace(const Emote& emote) const
    {
        return ::Load(m_facePath)(emote);
    }
}
