#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>
#include <Siv3D/FormatLiteral.hpp>

using namespace s3d::Literals::FormatLiterals;

namespace abyss
{
    TempKey TempKey::ItemGet(const s3d::String& mapName, s3d::uint32 id)
    {
        return TempKey(U"[{}]ItemGet-{}"_fmt(mapName, id));
    }
    TempKey TempKey::MidBossKill(const s3d::String& mapName, s3d::uint32 id)
    {
        return TempKey(U"[{}]MidBossKill-{}"_fmt(mapName, id));
    }
    TempKey TempKey::EventComplete(const s3d::String& mapName, s3d::uint32 id, s3d::uint32 phase)
    {
        return TempKey(U"[{}]EventComplete-{}-{}"_fmt(mapName, id, phase));
    }
}
