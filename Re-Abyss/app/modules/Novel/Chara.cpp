#include <abyss/modules/Novel/Chara.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    using namespace abyss::Resource;

    abyss::TexturePacker Load(const s3d::FilePath& path)
    {
        return Assets::Main()->loadTexturePacker(path);
    }
}

namespace abyss::Novel
{
    bool Chara::isFindFace(const Face& face) const
    {
        return ::Load(m_facePath).isContain(face);
    }

    s3d::Texture Chara::getFace(const Face& face) const
    {
        return ::Load(m_facePath)(face);
    }
}
